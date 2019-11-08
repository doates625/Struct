/**
 * @file Struct.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <Struct.h>

/**
 * @brief Constructs Struct object
 * @param data Pointer to byte array
 * @param endian Endian-ness of data
 */
Struct::Struct(uint8_t* data, endian_t endian)
{
	this->data = data;
	this->endian = endian;
	this->idx = 0;
}

/**
 * @brief Sets data array pointer and resets
 * @param data Pointer to byte array
 * @return Reference to this
 */
Struct& Struct::set_data(uint8_t* data)
{
	this->data = data;
	return reset();
}

/**
 * @brief Returns pointer to byte array
 */
uint8_t* Struct::get_data()
{
	return data;
}

/**
 * @brief Resets get or set state
 */
Struct& Struct::reset()
{
	idx = 0;
	return *this;
}

/**
 * @brief Sets next free bytes in struct
 * @param bytes Array of bytes to copy from
 * @param num_bytes Number of bytes to copy
 */
Struct& Struct::set_bytes(uint8_t* bytes, uint32_t num_bytes)
{
	// Reset on state change
	if (state == state_get)
	{
		state = state_set;
		idx = 0;
	}

	// Set data
	uint32_t idx_end = idx + num_bytes - 1;
	if (endian == lsb_first)
	{
		// LSB first - write in ascending order
		for (uint32_t i = 0; i < num_bytes; i++)
		{
			data[idx + i] = bytes[i];
		}
	}
	else
	{
		// MSB first - write in descending order
		for (uint32_t i = 0; i < num_bytes; i++)
		{
			data[idx_end - i] = bytes[i];
		}
	}
	idx = idx_end + 1;

	// Return self-ref
	return *this;
}

/**
 * @brief Gets next unread bytes in struct
 * @param bytes Array of bytes to copy into
 * @param Number of bytes to copy
 */
Struct& Struct::get_bytes(uint8_t* bytes, uint32_t num_bytes)
{
	// Reset on state change
	if (state == state_set)
	{
		state = state_get;
		idx = 0;
	}

	// Get data
	uint32_t idx_end = idx + num_bytes - 1;
	if (endian == lsb_first)
	{
		// LSB first - read in ascending order
		for (uint32_t i = 0; i < num_bytes; i++)
		{
			bytes[i] = data[idx + i];
		}
	}
	else
	{
		// MSB first - read in descending order
		for (uint32_t i = 0; i < num_bytes; i++)
		{
			bytes[i] = data[idx_end - i];
		}
	}
	idx = idx_end + 1;

	// Return self-ref
	return *this;
}