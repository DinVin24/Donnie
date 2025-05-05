class GameException : public std::exception {
protected:
    std::string message;
public:
    GameException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class AssetLoadException : public GameException {
public:
    AssetLoadException(const std::string& asset)
        : GameException("N-am putut incarca urmatorul asset: " + asset) {}
};

