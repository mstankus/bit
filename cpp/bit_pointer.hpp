// ============================== BIT POINTER =============================== //
// Project:         The C++ Bit Library
// Name:            bit_pointer.hpp
// Description:     A class representing a pointer to a bit
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2015-2017]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _BIT_POINTER_HPP_INCLUDED
#define _BIT_POINTER_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "bit_details.hpp"
// Third-party libraries
// Miscellaneous
namespace bit {
// ========================================================================== //



/* ****************************** BIT POINTER ******************************* */
// Bit pointer class definition
template <class UIntType>
class bit_pointer
{
    // Assertions
    static_assert(binary_digits<UIntType>::value, "");
    
    // Friendship
    template <class> friend class bit_pointer;
    
    // Types
    public:
    using underlying_type = UIntType;
    using size_type = std::size_t;
    using difference_type = std::intmax_t;

    // Lifecycle
    public:
    bit_pointer() noexcept = default;
    template <class T> 
    constexpr bit_pointer(const bit_pointer<T>& other) noexcept;
    explicit constexpr bit_pointer(std::nullptr_t) noexcept;
    constexpr bit_pointer(std::nullptr_t, size_type);
    explicit constexpr bit_pointer(underlying_type* ptr) noexcept;
    constexpr bit_pointer(underlying_type* ptr, size_type pos);
    
    // Assignment
    public:
    bit_pointer& operator=(std::nullptr_t) noexcept;
    bit_pointer& operator=(const bit_pointer& other) noexcept;
    template <class T> 
    bit_pointer& operator=(const bit_pointer<T>& other) noexcept;
    bit_pointer& operator=(underlying_type* ptr) noexcept;
    
    // Conversion
    public:
    explicit constexpr operator bool() const noexcept;

    // Access
    public:
    constexpr bit_reference<UIntType> operator*() const noexcept;
    constexpr bit_reference<UIntType>* operator->() const noexcept;
    constexpr bit_reference<UIntType> operator[](difference_type n) const;
    
    // Increment and decrement operators
    public:
    bit_pointer& operator++();
    bit_pointer& operator--();
    bit_pointer operator++(int);
    bit_pointer operator--(int);
    constexpr bit_pointer operator+(difference_type n) const;
    constexpr bit_pointer operator-(difference_type n) const;
    bit_pointer& operator+=(difference_type n);
    bit_pointer& operator-=(difference_type n);

    // Implementation details: data members
    private:
    bit_reference<UIntType> _ref;

    // Non-member arithmetic operators
    template <class T>
    friend constexpr bit_pointer<T> operator+(
        typename bit_pointer<T>::difference_type n,
        bit_pointer<T> x
    );
    template <class T, class U>
    friend constexpr typename std::common_type<
        typename bit_pointer<T>::difference_type,
        typename bit_pointer<U>::difference_type
    >::type operator-(
        bit_pointer<T> lhs,
        bit_pointer<U> rhs
    );

    // Comparison operators
    template <class T, class U>
    friend constexpr bool operator==(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
    template <class T, class U>
    friend constexpr bool operator!=(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
    template <class T, class U>
    friend constexpr bool operator<(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
    template <class T, class U>
    friend constexpr bool operator<=(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
    template <class T, class U>
    friend constexpr bool operator>(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
    template <class T, class U>
    friend constexpr bool operator>=(
        bit_pointer<T> lhs, 
        bit_pointer<U> rhs
    ) noexcept;
};

// Make functions
template <class T>
constexpr bit_pointer<T> make_bit_pointer(
  T* ptr
) noexcept;
template <class T>
constexpr bit_pointer<T> make_bit_pointer(
  T* ptr,
  typename bit_pointer<T>::size_type pos
);
/* ************************************************************************** */



// ------------------------- BIT POINTER: LIFECYCLE ------------------------- //
// Implicitly constructs a bit pointer from another bit pointer
template <class UIntType>
template <class T> 
constexpr bit_pointer<UIntType>::bit_pointer(
    const bit_pointer<T>& other
) noexcept
: _ref(other._ref)
{
}

// Explicitly constructs an aligned bit pointer from a null pointer
template <class UIntType>
constexpr bit_pointer<UIntType>::bit_pointer(
    std::nullptr_t
) noexcept
: _ref(nullptr)
{
}

// Explicitly constructs an unaligned bit pointer from a null pointer
template <class UIntType>
constexpr bit_pointer<UIntType>::bit_pointer(
    std::nullptr_t, 
    size_type
)
: _ref(nullptr, 0)
{
}

// Explicitly constructs an aligned bit pointer from a pointer
template <class UIntType>
constexpr bit_pointer<UIntType>::bit_pointer(
    underlying_type* ptr
) noexcept
: _ref(ptr)
{
}

// Explicitly constructs an unaligned bit pointer from a pointer
template <class UIntType>
constexpr bit_pointer<UIntType>::bit_pointer(
    underlying_type* ptr, 
    size_type pos
)
: _ref(ptr, pos)
{
}
// -------------------------------------------------------------------------- //



// ------------------------ BIT POINTER: ASSIGNMENT ------------------------- //
// Assigns a null pointer to the bit pointer
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator=(
    std::nullptr_t
) noexcept
{
    _ref._ptr = nullptr;
    _ref._mask = 0;
    return *this;
}

// Copies a bit pointer to the bit pointer
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator=(
    const bit_pointer& other
) noexcept
{
    _ref._ptr = other._ptr;
    _ref._mask = other._mask;
    return *this;
}

// Assigns a bit pointer to the bit pointer
template <class UIntType>
template <class T> 
bit_pointer<UIntType>& bit_pointer<UIntType>::operator=(
    const bit_pointer<T>& other
) noexcept
{
    _ref._ptr = other._ptr;
    _ref._mask = other._mask;
    return *this;
}

// Assigns a pointer to the aligned bit of a value to the bit pointer
template <class UIntType> 
bit_pointer<UIntType>& bit_pointer<UIntType>::operator=(
    underlying_type* ptr
) noexcept
{
    _ref._ptr = ptr;
    _ref._mask = 1;
    return *this;
}
// -------------------------------------------------------------------------- //



// ------------------------ BIT POINTER: CONVERSION ------------------------- //
// Returns true if the bit pointer is null, false otherwise
template <class UIntType>
constexpr bit_pointer<UIntType>::operator bool(
) const noexcept
{
    return _ref._ptr;
}
// -------------------------------------------------------------------------- //



// -------------------------- BIT POINTER: ACCESS --------------------------- //
// Gets a bit reference from the bit pointer
template <class UIntType>
constexpr bit_reference<UIntType> bit_pointer<UIntType>::operator*(
) const noexcept
{
    return _ref;
}

// Gets a pointer to a bit reference
template <class UIntType>
constexpr bit_reference<UIntType>* bit_pointer<UIntType>::operator->(
) const noexcept
{
    return std::addressof(const_cast<bit_reference<UIntType>&>(_ref));
}

// Gets a bit reference, decrementing or incrementing the pointer
template <class UIntType>
constexpr bit_reference<UIntType> bit_pointer<UIntType>::operator[](
    difference_type n
) const
{
    constexpr difference_type digits = binary_digits<underlying_type>::value;
    const difference_type sum = _ref.position() + n;
    difference_type diff = sum / digits;
    if (sum < 0 && diff * digits != sum) {
        --diff;
    }
    return bit_reference<UIntType>(_ref._ptr + diff, sum - diff * digits);
}
// -------------------------------------------------------------------------- //



// ------------- BIT POINTER: INCREMENT AND DECREMENT OPERATORS ------------- //
// Increments the bit pointer and returns it
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator++(
)
{
    using type = typename std::remove_cv<underlying_type>::type;
    constexpr size_type digits = binary_digits<underlying_type>::value;
    constexpr type one = 1;
    constexpr type mask = one; 
    const size_type pos = _ref.position();
    if (pos + 1 < digits) {
        _ref._mask <<= 1;
    } else {
        ++_ref._ptr;
        _ref._mask = mask;
    }
    return *this;
}

// Decrements the bit pointer and returns it
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator--(
)
{
    using type = typename std::remove_cv<underlying_type>::type;
    constexpr size_type digits = binary_digits<underlying_type>::value;
    constexpr type one = 1;
    constexpr type mask = static_cast<type>(one << (digits - 1)); 
    const size_type pos = _ref.position();
    if (pos) {
        _ref._mask >>= 1;
    } else {
        --_ref._ptr;
        _ref._mask = mask;
    }
    return *this;
}

// Increments the bit pointer and returns the old one
template <class UIntType>
bit_pointer<UIntType> bit_pointer<UIntType>::operator++(
    int
)
{
    bit_pointer old = *this;
    ++(*this);
    return old;
}

// Decrements the bit pointer and returns the old one
template <class UIntType>
bit_pointer<UIntType> bit_pointer<UIntType>::operator--(
    int
)
{
    bit_pointer old = *this;
    --(*this);
    return old;
}

// Looks forward several bits and gets a pointer at this position
template <class UIntType>
constexpr bit_pointer<UIntType> bit_pointer<UIntType>::operator+(
    difference_type n
) const
{
    constexpr difference_type digits = binary_digits<underlying_type>::value;
    const difference_type sum = _ref.position() + n;
    difference_type diff = sum / digits;
    if (sum < 0 && diff * digits != sum) {
        --diff;
    }
    return bit_pointer(_ref._ptr + diff, sum - diff * digits);
}

// Looks backward several bits and gets a pointer at this position
template <class UIntType>
constexpr bit_pointer<UIntType> bit_pointer<UIntType>::operator-(
    difference_type n
) const
{
    constexpr difference_type digits = binary_digits<underlying_type>::value;
    const difference_type sum = _ref.position() - n;
    difference_type diff = sum / digits;
    if (sum < 0 && diff * digits != sum) {
        --diff;
    }
    return bit_pointer(_ref._ptr + diff, sum - diff * digits);
}

// Increments the pointer by several bits and returns it
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator+=(
    difference_type n
)
{
    *this = *this + n;
    return *this;
}

// Decrements the pointer by several bits and returns it
template <class UIntType>
bit_pointer<UIntType>& bit_pointer<UIntType>::operator-=(
    difference_type n
)
{
    *this = *this - n;
    return *this;
}
// -------------------------------------------------------------------------- //



// -------------- BIT POINTER: NON-MEMBER ARITHMETIC OPERATORS -------------- //
// Advances the bit pointer several times
template <class T>
constexpr bit_pointer<T> operator+(
    typename bit_pointer<T>::difference_type n,
    bit_pointer<T> x
)
{
    return x + n;
}

// Computes the distance in bits separating two bit pointers
template <class T, class U>
constexpr typename std::common_type<
    typename bit_pointer<T>::difference_type,
    typename bit_pointer<U>::difference_type
>::type operator-(
    bit_pointer<T> lhs,
    bit_pointer<U> rhs
)
{
    using lhs_type = typename bit_pointer<T>::difference_type;
    using rhs_type = typename bit_pointer<U>::difference_type;
    using difference_type = typename std::common_type<lhs_type, rhs_type>::type;
    constexpr difference_type lhs_digits = binary_digits<T>::value;
    constexpr difference_type rhs_digits = binary_digits<U>::value;
    constexpr difference_type digits = rhs_digits;
    static_assert(lhs_digits == rhs_digits, "");
    const difference_type main = lhs._ref.address() - rhs._ref.address();
    return main * digits + (lhs._ref.position() - rhs._ref.position());
}
// -------------------------------------------------------------------------- //



// ------------------- BIT POINTER: COMPARISON OPERATORS -------------------- //
// Checks if the left hand side is equal to the right hand side
template <class T, class U>
constexpr bool operator==(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() == rhs._ref.address() 
        && lhs._ref.position() == rhs._ref.position();
}

// Checks if the left hand side is non equal to the right hand side
template <class T, class U>
constexpr bool operator!=(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() != rhs._ref.address() 
        || lhs._ref.position() != rhs._ref.position();
}

// Checks if the left hand side is less than the right hand side
template <class T, class U>
constexpr bool operator<(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() < rhs._ref.address() 
        || (lhs._ref.address() == rhs._ref.address()
            && lhs._ref.position() < rhs._ref.position());
}

// Checks if the left hand side is less than or equal to the right hand side
template <class T, class U>
constexpr bool operator<=(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() < rhs._ref.address() 
        || (lhs._ref.address() == rhs._ref.address()
            && lhs._ref.position() <= rhs._ref.position());
}

// Checks if the left hand side is greater than the right hand side
template <class T, class U>
constexpr bool operator>(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() > rhs._ref.address() 
        || (lhs._ref.address() == rhs._ref.address()
            && lhs._ref.position() > rhs._ref.position());
}

// Checks if the left hand side is greater than or equal to the right hand side
template <class T, class U>
constexpr bool operator>=(
    bit_pointer<T> lhs, 
    bit_pointer<U> rhs
) noexcept
{
    return lhs._ref.address() > rhs._ref.address() 
        || (lhs._ref.address() == rhs._ref.address()
            && lhs._ref.position() >= rhs._ref.position());
}
// -------------------------------------------------------------------------- //



// ---------------------- BIT POINTER: MAKE FUNCTIONS ----------------------- //
// Constructs an aligned bit pointer
template <class T>
constexpr bit_pointer<T> make_bit_pointer(
  T* ptr
) noexcept
{
    return bit_pointer<T>(ptr);
}

// Constructs an unaligned bit pointer
template <class T>
constexpr bit_pointer<T> make_bit_pointer(
  T* ptr,
  typename bit_pointer<T>::size_type pos
)
{
    return bit_pointer<T>(ptr, pos);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace bit
#endif // _BIT_POINTER_HPP_INCLUDED
// ========================================================================== //
