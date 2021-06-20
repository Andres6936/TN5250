/* tn5250 -- an implentation of the 5250 telnet protocol.
 * Copyright (C) 2000-2008 Jason M. Felice
 *
 * This file is part of TN5250.
 *
 * TN5250 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * TN5250 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef CONF_H
#define CONF_H

#include <string>
#include <vector>
#include <utility>
#include <cstdint>

struct _Tn5250ConfigStr
{
	struct _Tn5250ConfigStr* next;
	struct _Tn5250ConfigStr* prev;
	char* name;
	char* value;
};

typedef struct _Tn5250ConfigStr Tn5250ConfigStr;

struct _Tn5250Config : private std::vector<std::pair<std::string, std::string>>
{
	std::int32_t ref = 1;
	Tn5250ConfigStr* vars = nullptr;

	// Constructor

	_Tn5250Config() noexcept = default;

	/**
	 * Associates the specified value with the specified key in this map
	 * (optional operation).
	 *
	 * @param key key with which the specified value is to be associated.
	 * @param value value to be associated with the specified key.
	 */
	void put(const std::string& key, const std::string& value) noexcept;

	/**
	 * Returns true if this map contains a mapping for the specified key.
	 *
	 * @param key key whose presence in this map is to be tested.
	 * @return true if this map contains a mapping for the specified key.
	 */
	const bool containsKey(const std::string& key) const noexcept;

	/**
	 * @brief Returns the value to which the specified key is mapped,
	 * or null if this map contains no mapping for the key.
	 *
	 * @param key the key whose associated value is to be returned.
	 * @return the value to which the specified key is mapped, or null
	 * if this map contains no mapping for the key.
	 */
	const std::string get(const std::string& key) const noexcept;
};

typedef struct _Tn5250Config Tn5250Config;

extern Tn5250Config* tn5250_config_ref(Tn5250Config* This);

extern void tn5250_config_unref(Tn5250Config* This);

extern int tn5250_config_load(Tn5250Config* This,
		const char* filen);

extern int tn5250_config_load_default(Tn5250Config* This);

extern int tn5250_config_parse_argv(Tn5250Config* This,
		int argc,
		char** argv);

extern const char* tn5250_config_get(Tn5250Config* This,
		const char* name);

extern int tn5250_config_get_bool(Tn5250Config* This,
		const char* name);

extern int tn5250_config_get_int(Tn5250Config* This,
		const char* name);

extern void tn5250_config_set(Tn5250Config* This,
		const char* name,
		const char* value);

extern void tn5250_config_unset(Tn5250Config* This,
		const char* name);

extern void tn5250_config_promote(Tn5250Config* This,
		const char* prefix);



#endif                /* CONF_H */

/* vi:set sts=3 sw=3: */
