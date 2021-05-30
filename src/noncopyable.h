//
// Created by 蔡同松 on 2021/5/29.
//

#ifndef ABA_COLLECTION_NONCOPYABLE_H
#define ABA_COLLECTION_NONCOPYABLE_H
namespace aba {
    class noncopyable {
    public:
        noncopyable() = default;
        ~noncopyable() = default;
    private:
        noncopyable(const noncopyable &) = delete;
        noncopyable &operator=(const noncopyable &) = delete;
    };
}
#endif //ABA_COLLECTION_NONCOPYABLE_H
