#include <HttpRequest.hpp>
namespace http
{
    // 设置请求方法
    bool HttpRequest::setMethod(const char *begin, const char *end)
    {
        assert(method_ == kInvalid);
        std::string temp(begin, end);
        if (temp == "GET")
        {
            method_ = kGet;
        }
        else if (temp == "POST")
        {
            method_ = kPost;
        }
        else if (temp == "PUT")
        {
            method_ = kPut;
        }
        else if (temp == "DELETE")
        {
            method_ = kDelete;
        }
        else if (temp == "OPTIONS")
        {
            method_ = kOptions;
        }
        else
        {
            method_ = kInvalid;
        }

        return method_ != kInvalid;
    }
    // 设置路径参数
    void HttpRequest::setPathParameters(const std::string &key, const std::string &value)
    {
        pathParameters_[key] = value;
    }
    // 获取路径参数值
    std::string HttpRequest::getPathParameters(const std::string &key) const
    {
        auto it = pathParameters_.find(key);
        if (it != pathParameters_.end())
        {
            return it->second;
        }
        return "";
    }
    // 设置查询参数
    void HttpRequest::setQueryParameters(const char *begin, const char *end)
    {
        std::string temp(begin, end);
        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        // 按照&分割多个查询参数
        while ((pos = temp.find('&', prev)) != std::string::npos)
        {
            std::string pair = temp.substr(prev, pos - prev);
            std::string::size_type equalPos = temp.find('=', prev);
            if (equalPos != std::string::npos)
            {
                std::string key = pair.substr(0, equalPos);
                std::string value = pair.substr(equalPos + 1);
                queryParameters_[key] = value;
            }
            prev = pos + 1;
        }
        // 最后一个&后面的查询参数
        std::string lastPair = temp.substr(prev);
        std::string::size_type equalPos = temp.find('=', prev);
        if (equalPos != std::string::npos)
        {
            std::string key = lastPair.substr(0, equalPos);
            std::string value = lastPair.substr(equalPos + 1);
            queryParameters_[key] = value;
        }
    }
    // 获取查询参数值
    std::string HttpRequest::getQueryParameters(const std::string &key) const
    {
        auto it = queryParameters_.find(key);
        if (it != queryParameters_.end())
        {
            return it->second;
        }
        return "";
    }
    // 添加请求头
    void HttpRequest::addHeader(const char *begin, const char *colon, const char *end)
    {
        std::string key(begin, colon);
        // 去空格
        while (++colon < end && isspace(*colon))
            ;
        while (end >= colon && isspace(*end))
        {
            end--;
        }
        std::string value(colon, end);
        headers_[key] = value;
    }
    // 获取请求头值
    std::string HttpRequest::getHeader(const std::string &key) const
    {
        auto it = headers_.find(key);
        if (it != headers_.end())
        {
            return it->second;
        }
        return "";
    }

    // 交换两个请求对象
    void HttpRequest::swap(HttpRequest &that)
    {
        std::swap(method_, that.method_);
        std::swap(version_, that.version_);
        std::swap(path_, that.path_);
        std::swap(pathParameters_, that.pathParameters_);
        std::swap(queryParameters_, that.queryParameters_);
        std::swap(receiveTime_, that.receiveTime_);
        std::swap(headers_, that.headers_);
        // std::swap(content_, that.content_);
        // std::swap(contentLength_, that.contentLength_);
    }
}