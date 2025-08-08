#include <string>
#include <unordered_map>

#include <muduo/base/Timestamp.h>

namespace http
{
    class HttpRequest
    {

    public:
        enum Method
        {
            kInvalid,
            kGet,
            kPost,
            kHead,
            kPut,
            kDelete,
            kOptions
        };
        // 构造函数
        HttpRequest() : method_(kInvalid), version_("Uknown") {}
        // 析构函数
        ~HttpRequest() = default;

        bool setMethod(const char *begin, const char *end);
        Method method() const { return method_; }

        void setVersion(const std::string &v) { version_ = v; }
        std::string getVersion() const { return version_; }

        void setPath(const char *begin, const char *end)
        {
            path_.assign(begin, end);
        };
        std::string getPath() const { return path_; }

        void setPathParameters(const std::string &key, const std::string &value);
        std::string getPathParameters(const std::string &key) const;

        void setQueryParameters(const char *begin, const char *end);
        std::string getQueryParameters(const std::string &key) const;

        void setReceiveTime(muduo::Timestamp t) { receiveTime_ = t; }
        muduo::Timestamp receiveTime() const { return receiveTime_; }

        void addHeader(const char *begin, const char *colon, const char *end);
        std::string getHeader(const std::string &key) const;
        std::unordered_map<std::string, std::string> headers() const
        {
            return headers_;
        }

        void setBody(const std::string &body) { content_ = body; }
        void setBody(const char *begin, const char *end)
        {
            if (end >= begin)
            {
                content_.assign(begin, end - begin);
            }
        }
        std::string getBody() const { return content_; }

        void setContentLength(uint64_t length) { contentLength_ = length; }
        uint64_t getContentLength() const { return contentLength_; }

        void swap(HttpRequest &that);

    private:
        Method method_;                                                // 请求方法
        std::string version_;                                          // HTTP版本
        std::string path_;                                             // 请求路径
        std::unordered_map<std::string, std::string> pathParameters_;  // 路径参数
        std::unordered_map<std::string, std::string> queryParameters_; // 查询参数
        muduo::Timestamp receiveTime_;                                 // 接受时间
        std::unordered_map<std::string, std::string> headers_;         // 请求头
        std::string content_;                                          // 请求体
        uint64_t contentLength_{0};                                    // 请求体长度
    };
} // namespace http