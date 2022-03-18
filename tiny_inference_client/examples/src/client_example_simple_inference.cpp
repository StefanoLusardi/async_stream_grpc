#include "infer_request.hpp"
#include <iostream>
#include <client_core.hpp>
#include <opencv2/opencv.hpp>


template<typename T>
constexpr std::vector<T> get_response_tensor(const tie::infer_response::tensor_info& tensor_info)
{
    return std::vector<T>{ (T*)tensor_info.data, (T*)tensor_info.data + tensor_info.count };
};

int main(int argc, char** argv)
{
    std::cout << "Running client_example_model_info" << "\n" << std::endl;
    tie::client_core::client_core client("localhost:50051");

    std::string imageFilepath{ "images/dog.jpg" };
    cv::Mat imageBGR = cv::imread(imageFilepath, cv::ImreadModes::IMREAD_COLOR);
    // cv::imshow("resizedImage", imageBGR);
    // cv::waitKey(0);

    cv::Mat resizedImageBGR, resizedImageRGB, resizedImage, preprocessedImage;

    // TODO: read inputDims from model
    // cv::resize(imageBGR, resizedImageBGR, cv::Size(inputDims.at(2), inputDims.at(3)), cv::InterpolationFlags::INTER_CUBIC);
    cv::resize(imageBGR, resizedImageBGR, cv::Size(224, 224), cv::InterpolationFlags::INTER_CUBIC);
    cv::cvtColor(resizedImageBGR, resizedImageRGB, cv::ColorConversionCodes::COLOR_BGR2RGB);
    resizedImageRGB.convertTo(resizedImage, CV_32F, 1.0 / 255);

    // cv::imshow("resizedImage", resizedImage);
    // cv::waitKey(0);

    cv::Mat channels[3];
    cv::split(resizedImage, channels);

    // Normalization parameters obtained from https://github.com/onnx/models/tree/master/vision/classification/squeezenet
    channels[0] = (channels[0] - 0.485) / 0.229;
    channels[1] = (channels[1] - 0.456) / 0.224;
    channels[2] = (channels[2] - 0.406) / 0.225;
    cv::merge(channels, 3, resizedImage);

    // cv::imshow("resizedImage", resizedImage);
    // cv::waitKey(0);

    // HWC to CHW
    cv::dnn::blobFromImage(resizedImage, preprocessedImage);

    auto request = tie::infer_request();
    request.data = { preprocessedImage.datastart, preprocessedImage.dataend };
    request.model_name = "models/squeezenet1.1-7.onnx";

    client.load_model(std::string(request.model_name));
    auto response = client.infer_sync(request);
    auto response_tensor = get_response_tensor<float>(response.tensors.at("squeezenet0_flatten0_reshape0"));

    return EXIT_SUCCESS;
}