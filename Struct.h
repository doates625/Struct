/**
 * @file Struct.h
 * @brief Class for interpreting byte arrays as C data types
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
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
	Struct& set_data(uint8_t* data);
	uint8_t* get_data();
	Struct& reset();

	// Generic Getters and Setters
	template <typename T> Struct& set(const T& val);
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

private:
	
	// Copy and assignment operators
	Struct(const Struct&);
	Struct& operator=(const Struct&);

};

/**
 * Method Definitions
 */

/**
 * @brief Sets next free bytes in struct to val
 * @param val Value to set [stdint or float]
 * @return Reference to this
 */
template <typename T>
Struct& Struct::set(const T& val)
{
	return set_bytes((uint8_t*)(&val), sizeof(T));
}

/**
 * @brief Interprets next unread bytes in struct as val
 * @param val Variable assigned to
 * @return Reference to this
 */
template <typename T>
Struct& Struct::get(T& val)
{
	return get_bytes((uint8_t*)(&val), sizeof(T));
}

/**
 * @brief Shorthand for get functionality
 * @return Value interpreted from bytes
 */
template <typename T>
Struct::operator T()
{
	T val;
	get(val);
	return val;
}

/**
 * Function Definitions
 */

/**
 * @brief Shorthand for set functionality
 * @param str Struct to assign data to
 * @param val Data to assign from
 * @return Reference to this
 */
template <typename T>
Struct& operator<<(Struct& str, const T& val)
{
	return str.set(val);
}

/**
 * @brief Shorthand for set functionality
 * @param val Data to assign from
 * @param str Struct to assign data to
 * @return Reference to this
 */
template <typename T>
Struct& operator>>(const T& val, Struct& str)
{
	return str.set(val);
}

/**
 * @brief Shorthand for get functionality
 * @param val Variable assigned to
 * @param str Struct to get data from
 * @return Reference to this
 */
template <typename T>
Struct& operator<<(T& val, Struct& str)
{
	return str.get(val);
}

/**
 * @brief Shorthand for get functionality
 * @param str Struct to get data from
 * @param val Variable assigned to
 * @return Reference to this
 */
template <typename T>
Struct& operator>>(Struct& str, T& val)
{
	return str.get(val);
}
