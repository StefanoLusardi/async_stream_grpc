#pragma once

#include <tie_engine/backend_interface.hpp>

#include <memory>
#include <algorithm>
#include <string_view>
#include <vector>
#include <map>

#include <onnxruntime_cxx_api.h>

// #if defined(WIN32)
// #pragma push(disable : C4244)
// #endif

#include <numeric>

// #if defined(WIN32)
// #pragma pop
// #endif

namespace tie::engine
{

class onnx_backend : public backend_interface
{
    struct session_info
    {
        struct model_info
        {
            explicit model_info(char* name, const std::vector<int64_t>& shape, ONNXTensorElementDataType type, const std::shared_ptr<Ort::AllocatorWithDefaultOptions>& allocator)
                : name{ name }
                , shape{ shape }
                , type{ type }
                , _allocator {allocator}
            {
            }

            ~model_info()
            {
                _allocator->Free(name);
            }


            char* name;
            std::vector<int64_t> shape;
            ONNXTensorElementDataType type;
            std::shared_ptr<Ort::AllocatorWithDefaultOptions> _allocator;
        };

        std::vector<model_info> inputs;
        std::vector<model_info> outputs;
        std::unique_ptr<Ort::Session> session;
    };

public:
    explicit onnx_backend() noexcept;
    ~onnx_backend();

    auto is_model_ready(const std::string& model_name, const std::string& model_version) const -> bool override;
    auto model_load(const std::string& model_name, const std::string& model_version) -> bool override;
    auto model_unload(const std::string& model_name, const std::string& model_version) -> bool override;
    auto model_metadata(const std::string& model_name, const std::string& model_version) -> common::model_metadata override;
    auto infer(const infer_request& infer_request) -> infer_response override;

private:
    std::unique_ptr<Ort::Env> _env;
    std::shared_ptr<Ort::AllocatorWithDefaultOptions> _allocator;
    std::map<std::string, session_info> _model_sessions;
};

}
