# ID
C++20 template class that generates a type for identifiers (aka ID's).
Tested with gcc 10.1.0

### Features
- based on user selected integral type
- orderable: can be a key in a set, map, etc.
- hashable: can be a key in an unordered_set, unordered_map, etc.
- value can be the invalid value
- output streamable


### Reference
Member Types | Description
-----------------------------------| ------------------------------------------------------------
`T` | Contained raw value type. Must be an unsigned integer.
`DISC = void` | Discriminator allows creation of unique types for the ID. `void` means no discrimination: all ID's of a given T are the same type. An empty class discriminator creates a unique type. A non-empty class discriminator creates a unique type and is declared a friend, allowing direct access to the contained raw type.
`INVALID_VALUE = 0` | Value to represent an invalid id internally.


Member Functions | Description
-----------------------------------| ------------------------------------------------------------
`ID()` | The empty default constructor which constructs an invalid instance.
`explicit ID(T raw_value)` | Construct an instance with value theID.
`auto raw_value()` | Returns the contained raw value. Only available if discriminator type is an empty class or void.
`explicit operator bool()` | Return true if not invalid.


Friend Functions | Description
-----------------------------------| ------------------------------------------------------------
`bool operator==(const ID<T>& l, const ID<T>& r) noexcept` | Equality check is provided. Required for hashing.
`bool operator<(const ID<T>& l, const ID<T>& r) noexcept` | Less than is provided. Required for ordering.
`std::ostream& operator<<(std::ostream& os, const ID<T>& theID)` | Output streaming available for logging, etc.
