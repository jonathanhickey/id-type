#pragma once
#include <ostream>
#include <concepts>


template<  // c++17 version
        typename T,             // the raw type
        typename DISC = void,   // the discriminator type
        T INVALID_VALUE = 0,    // value internally representing an invalid id
        typename A = typename std::enable_if<std::is_integral_v<T>> // must be an integer
>
class ID final {
private:
    T id;

public:
    // default initialization is 0 which is the invalid ID
    ID() : id{INVALID_VALUE} {}

    // construct with the raw value
    explicit ID(T raw_value) : id(raw_value) {}

    // default destructor
    ~ID() = default;

    // make copyable
    ID(const ID& r) = default;
    ID& operator=(const ID& r) = default;

    // note the move ctor and assignment are not deleted,
    // thus any attempt to move an ID will result in a copy.
    // this design was chosen because the contained type must be fundamental.

    // make the discriminator class a friend, so that the discriminator can access the raw value.
    // if DISC is void or an empty class declaring it a friend does nothing.
    friend DISC;

    // if the discriminator is void or an empty class provide a raw_value function. c++17 version.
    template <typename U = DISC>
    std::enable_if_t<std::is_void_v<U> || std::is_empty_v<U>, T>
    raw_value() { return id; }

    // check if valid id
    explicit operator bool() const { return id != INVALID_VALUE; }

    // hasher for unordered containers
    struct Hasher {
        size_t operator()(const ID &s) const noexcept { return std::hash<T>{}(s.id); }
    };

    // these related global operators need access to id which is private

    template<typename T1, typename F1>
    friend bool operator==(const ID<T1, F1>& l, const ID<T1, F1>& r) noexcept;

    template<typename T1, typename F1>
    friend bool operator<(const ID<T1, F1>& l, const ID<T1, F1>& r) noexcept;

    template<typename T1, typename F1>
    friend std::ostream& operator<<(std::ostream& os, const ID<T1, F1>& theID);
};

// equality check is allowed. required for hashing.
template<typename T, typename F>
bool operator==(const ID<T, F>& l, const ID<T, F>& r) noexcept {
    return l.id == r.id;
}

// less than is allowed. required for ordering.
template<typename T, typename F>
bool operator<(const ID<T, F>& l, const ID<T, F>& r) noexcept {
    return l.id < r.id;
}

// available for logging
template<typename T, typename F>
inline std::ostream& operator<<(std::ostream& os, const ID<T,F>& theID) {
    os << theID.id;
    return os;
}
