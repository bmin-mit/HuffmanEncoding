//
// Created by Doan Ngoc Binh Minh on 9/13/26.
//

export module core:errors;

import std;

export namespace core {
    class NotImplemented : public std::logic_error {
        std::string _text;

        NotImplemented(const char *message, const char *function)
            : std::logic_error("Not Implemented") {
            _text = message;
            _text += " : ";
            _text += function;
        };

    public:
        NotImplemented()
            : NotImplemented("Not Implememented", __FUNCTION__) {
        }

        explicit NotImplemented(const char *message)
            : NotImplemented(message, __FUNCTION__) {
        }

        const char *what() const throw() override {
            return _text.c_str();
        }
    };
}
