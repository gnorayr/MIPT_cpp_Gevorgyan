class IOWrapper {
public:
    IOWrapper() = delete;
    IOWrapper(handle_t resource)
            : resource_(resource)
    {}
    IOWrapper(IOWrapper &rhs) = delete;
    IOWrapper(IOWrapper &&rhs)
            : resource_(rhs.resource_)
    {
        rhs.resource_ = kNullHandle;
    }

    ~IOWrapper() {
        if (resource_ != kNullHandle) {
            raw_close(resource_);
        }
    }

    IOWrapper& operator=(IOWrapper &&rhs) {
        resource_ = std::move(rhs.resource_);
        rhs.resource_ = kNullHandle;
        return *this;
    }
    IOWrapper& operator=(IOWrapper &rhs) = delete;

    void Write(const std::string& content) {
        raw_write(resource_, content);
    }
private:
    handle_t resource_;
};