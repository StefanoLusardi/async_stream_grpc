#pragma once

#include <string_view>
#include <vector>

namespace tie::backend
{
struct infer_response
{
    std::string_view model_name;
    std::string_view data;
    std::string_view score;
};

}