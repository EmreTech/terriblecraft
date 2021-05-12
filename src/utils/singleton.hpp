#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/**
 * @brief Prohibits children of this class to be copyable.
 */
struct NonCopyable {
  NonCopyable() = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};

/**
 * @brief Prohibits children of this class to be movable.
 */
struct NonMovable {
  NonMovable(NonMovable &&) = delete;
  NonMovable &operator=(NonMovable &&) = delete;

protected:
  NonMovable() = default;
};

/**
 * @brief Prohibits children of this class to be copyable and movable.
 */
struct Singleton : public NonMovable, public NonCopyable {};

#endif