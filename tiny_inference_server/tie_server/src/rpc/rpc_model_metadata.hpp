#pragma once

#include "rpc_unary_async.hpp"
#include "rpc_io.hpp"

namespace tie::server
{
class rpc_model_metadata 
    : public rpc_unary_async
    , public rpc_io<inference::ModelMetadataRequest, inference::ModelMetadataResponse>
{
public:
    explicit rpc_model_metadata(
        const uint64_t id,
        const std::shared_ptr<inference::GRPCInferenceService::AsyncService>& service,
        const std::shared_ptr<grpc::ServerCompletionQueue>& cq,
        const std::shared_ptr<engine::engine_interface>& engine);
    ~rpc_model_metadata() override;

    void setup_request() override;
    void create_rpc() override;
    void process_request() override;
    void write_response() override;
};

}

/*
message ModelMetadataRequest
{
    string name = 1;
    string version = 2;
}

message ModelMetadataResponse
{
    message TensorMetadata
    {
        string name = 1;
        string datatype = 2;
        repeated int64 shape = 3;
    }
    string name = 1;
    repeated string versions = 2;
    string platform = 3;
    repeated TensorMetadata inputs = 4;
    repeated TensorMetadata outputs = 5;
}
*/