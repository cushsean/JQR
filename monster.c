#include "monster_builder.h" // Generated from 'flatcc'

#undef ns
#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(MyGame_Sample, x)

#define c_vec_len(V) (sizeof(V)/sizeof((V)[0]))

#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)

int create_monster_bottom_up(flatcc_builder_t *B, int flexible){
	
	// Create two variables to store the FB string and damage for the weapons
	flatbuffers_string_ref_t weapon_one_name = 
		flatbuffers_string_create_str(B, "Sword");
	uint16_t weapon_one_damage = 3;
	
	flatbuffers_string_ref_t weapon_two_name = 
		flatbuffers_string_create_str(B, "Axe");
	uint16_t weapon_two_damage = 3;


	// Create the weapons from the previously created variables
	ns(Weapon_ref_t) sword = ns(Weapon_create)(B, weapon_one_name, 
		weapon_one_damage);
	ns(Weapon_ref_t) axe = ns(Weapon_create)(B, weapon_two_name, 
		weapon_two_damage);

	// Create a FB string to store a monster's name
	flatbuffers_string_ref_t name = flatbuffers_string_create_str(B, "Orc");


	// Create an array of numbers (each representing possible loot) and 
	// convert the array into a FB vector
	uint8_t treasure[10];
	for(int i = 0; i < sizeof(treasure); i++)
		treasure[i] = i;
	flatbuffers_uint8_vec_ref_t inventory;
	inventory = flatbuffers_uint8_vec_create(B, treasure, c_vec_len(treasure));


	// Another way to create a vector like we did for inventory
	ns(Weapon_vex_start(B));
	ns(Weapon_vec_push(B, sword));
	ns(Weapon_vec_push(B, axe));
	ns(Weapon_vec_ref_t) weapons = ns(Weapons_ves_end(B));


	// Create a Vec3 to represent the Orc's position in 3-Dimentional space
	ns(Vec3_t) pos = { 1.0f, 2.0f, 3.0f);


	// Set hit points and mana
	uint16_t hp = 300;
	uint16_t mana = 150;

	


}