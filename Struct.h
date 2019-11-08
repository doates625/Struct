/**
 * @file Struct.h
 * @brief Class for interpreting byte arrays as C data types
 * @author Dan Oates (WPI Class of 2020)
 */
#include <stdint.h>

/**
 * Class Declaration
 */
class Struct
{
public:

	// Endian Enum
	typedef enum
	{
		msb_first,
		lsb_first,
	}
	endian_t;
	
	// Construction and Initialization
	Struct(uint8_t* data, endian_t endian = lsb_first);
	uint8_t* get_data();
	Struct& reset();

	// Generic Getters and Setters
	template <typename T> Struct& set(T val);
	template <typename T> Struct& operator<<(T val);
	template <typename T> Struct& get(T& val);
	template <typename T> operator T();

protected:

	// Fields
	uint8_t* data;
	endian_t endian;
	uint32_t idx;
	enum {
		state_set,
		state_get,
	} state;

	// Methods
	Struct& set_bytes(uint8_t* bytes, uint32_t num_bytes);
	Struct& get_bytes(uint8_t* bytes, uint32_t num_bytes);
};

/**
 * @brief Sets next free bytes in struct to val
 * @param val Value to set [stdint or float]
 * @return Reference to this
 */
template <typename T>
Struct& Struct::set(T val)
{
	return set_bytes((uint8_t*)(&val), sizeof(T));
}

/**
 * @brief Operator equivalent to set
 * @param val Value to set [stdint or float]
 * @return Reference to this
 */
template <typename T>
Struct& Struct::operator<<(T val)
{
	return set(val);
}

/**
 * @brief Interprets next unread bytes as val
 * @param val Reference to value assigned to
 * @return Reference to this
 */
template <typename T>
Struct& Struct::get(T& val)
{
	return get_bytes((uint8_t*)(&val), sizeof(T));
}

/**
 * @brief Interprets next unread bytes as val
 * @return Value interpreted from bytes
 */
template <typename T>
Struct::operator T()
{
	T val;
	get(val);
	return val;
}