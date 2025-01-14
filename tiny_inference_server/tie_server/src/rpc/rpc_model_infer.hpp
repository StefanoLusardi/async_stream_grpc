#pragma once

#include "rpc_unary_async.hpp"
#include "rpc_io.hpp"

namespace tie::server
{

class rpc_model_infer
    : public rpc_unary_async
    , public rpc_io<inference::ModelInferRequest, inference::ModelInferResponse>
{
public:
    explicit rpc_model_infer(
        const uint64_t id,
        const std::shared_ptr<inference::GRPCInferenceService::AsyncService>& service,
        const std::shared_ptr<grpc::ServerCompletionQueue>& cq,
        const std::shared_ptr<engine::engine_interface>& engine);
    ~rpc_model_infer() override;

    void setup_request() override;
    void create_rpc() override;
    void process_request() override;
    void write_response() override;
};

}

/*
message InferParameter
{
    oneof parameter_choice
    {
        bool bool_param = 1;
        int64 int64_param = 2;
        string string_param = 3;
        double double_param = 4;
    }
}
message InferTensorContents
{
    repeated bool bool_contents = 1;
    repeated int32 int_contents = 2;
    repeated int64 int64_contents = 3;
    repeated uint32 uint_contents = 4;
    repeated uint64 uint64_contents = 5;
    repeated float fp32_contents = 6;
    repeated double fp64_contents = 7;
    repeated bytes bytes_contents = 8;
}
message ModelInferRequest
{
    message InferInputTensor
    {
        string name = 1;
        string datatype = 2;
        repeated int64 shape = 3;
        map<string, InferParameter> parameters = 4;
        InferTensorContents contents = 5;
    }
    message InferRequestedOutputTensor
    {
        string name = 1;
        map<string, InferParameter> parameters = 2;
    }
    string model_name = 1;
    string model_version = 2;
    string id = 3;
    map<string, InferParameter> parameters = 4;
    repeated InferInputTensor inputs = 5;
    repeated InferRequestedOutputTensor outputs = 6;
    repeated bytes raw_input_contents = 7;
}
message ModelInferResponse
{
    message InferOutputTensor
    {
        string name = 1;
        string datatype = 2;
        repeated int64 shape = 3;
        map<string, InferParameter> parameters = 4;
        InferTensorContents contents = 5;
    }
    string model_name = 1;
    string model_version = 2;
    string id = 3;
    map<string, InferParameter> parameters = 4;
    repeated InferOutputTensor outputs = 5;
    repeated bytes raw_output_contents = 6;
}
*/