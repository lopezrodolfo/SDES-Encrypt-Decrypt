#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "simplified_des.h"

const uint8_t s1_box[16] = { 5, 2, 1, 6, 3, 4, 7, 0, 1, 4, 6, 2, 0, 7, 5, 3 };
const uint8_t s2_box[16] = { 4, 0, 6, 5, 7, 1, 3, 2, 5, 3, 0, 7, 6, 2, 1, 4 };

uint8_t expand(uint8_t input) {
	uint8_t bit1 = (input >> 5) & 1;
	uint8_t bit2 = (input >> 4) & 1;
	uint8_t bit3 = (input >> 3) & 1;
	uint8_t bit4 = (input >> 2) & 1;
	uint8_t bit5 = (input >> 1) & 1;
	uint8_t bit6 = input & 1;

	uint8_t result = (bit1 << 7) | (bit2 << 6) | (bit4 << 5) | (bit3 << 4) 
						| (bit4 << 3) | (bit3 << 2) | (bit5 << 1) | bit6;
	return result;
}

uint8_t confuse(uint8_t input) {
	uint8_t left_half = input >> 4;
	uint8_t right_half = input & 0xF;

	uint8_t substituted_left = s1_box[left_half];
	uint8_t substituted_right = s2_box[right_half];

	return (substituted_left << 3) | substituted_right;
}

uint8_t feistel(uint8_t input, uint8_t key) {
	uint8_t expanded = expand(input);
	uint8_t result = confuse(expanded ^ key);
	return result;
}

uint16_t feistel_round(uint16_t input, uint8_t key) {
	uint8_t left_half = input >> 6;
	uint8_t right_half = input & 0x3F;

	uint16_t result = left_half ^ feistel(right_half, key);

	result = result | (right_half << 6);
	return result;
}

uint8_t *generate_round_keys(uint16_t original_key, unsigned int num_rounds) {

	if (num_rounds > 9) {
		return NULL;
	}

	uint8_t *round_keys = calloc(num_rounds, sizeof(uint8_t));
	round_keys[0] = original_key >> 1;

	for (unsigned int i = 1; i < num_rounds; i++) {
		unsigned int num_rotated_bits = i - 1;
		uint8_t key = (original_key << num_rotated_bits) & 0xFF;
		if (num_rotated_bits > 0) {
			uint8_t rotated_bits = ((original_key << (num_rotated_bits - 1)) & 0xFF00) >> 8;
			key = key | rotated_bits;
		}
		round_keys[i] = key;
	}
	return round_keys;
}

uint16_t sdes_encrypt(uint16_t unencrypted_data, uint8_t *round_keys, int num_rounds) {
	uint16_t encrypted_data = unencrypted_data;
    
	for (int i = 0; i < num_rounds; i++) {
		encrypted_data = feistel_round(encrypted_data, round_keys[i]);
	}

	uint8_t left_half = encrypted_data >> 6;
	uint8_t right_half = encrypted_data & 0x3F;
	return (right_half << 6) | left_half;
}

uint16_t sdes_decrypt(uint16_t encrypted_data, uint8_t *round_keys, int num_rounds) {
	uint16_t decrypted_data = encrypted_data;

	for (int i = 0; i < num_rounds; i++) {
		decrypted_data = feistel_round(decrypted_data, round_keys[(num_rounds - 1) - i]);
	}

	uint8_t left_half = decrypted_data >> 6;
	uint8_t right_half = decrypted_data & 0x3F;
	return (right_half << 6) | left_half;
}