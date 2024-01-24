
#pragma once

#include <cstdint>
#include "../engine/common/vec.hpp"
#include "../engine/common/grid.hpp"

/**
 * @brief Cell of the collision grid
 * 
 */
struct CollisionCell {
    static constexpr uint8_t cell_capacity = 4;
    static constexpr uint8_t max_cell_idx  = 3;

	uint32_t objects_count = 0;
    uint32_t objects[cell_capacity] = {};

	CollisionCell() = default;

	/**
	 * @brief Add an atom to the cell
	 * 
	 * @param id id of the atom
	 */
	void addAtom(uint32_t id) {
        objects[objects_count] = id;
        objects_count += objects_count < max_cell_idx;
	}

	/**
	 * @brief Clear the cell
	 * 
	 */
	void clear() {
		objects_count = 0;
	}

	/**
	 * @brief Remove an atom from the cell
	 * 
	 * @param id id of the atom
	 */
    void remove(uint32_t id) {
        for (uint32_t i = 0; i < objects_count; ++i) {
            if (objects[i] == id) {
                objects[i] = objects[objects_count - 1];
                --objects_count;
                return;
            }
        }
    }
};

struct CollisionGrid : public Grid<CollisionCell> {
	CollisionGrid() : Grid<CollisionCell>() {}

	/**
	 * @brief Construct a new Collision Grid object
	 * 
	 * @param width width of the grid
	 * @param height height of the grid
	 */
	CollisionGrid(int32_t width, int32_t height) : Grid<CollisionCell>(width, height) {}

	/**
	 * @brief Add an atom to the grid
	 * 
	 * @param x x coordinate of the atom
	 * @param y y coordinate of the atom
	 * @param atom id of the atom
	 * @return true if the atom was added
	 */
	bool addAtom(uint32_t x, uint32_t y, uint32_t atom) {
		const uint32_t id = x * height + y;
		data[id].addAtom(atom);
		return true;
	}

	/**
	 * @brief Remove an atom from the grid
	 * 
	 * @param x x coordinate of the atom
	 * @param y y coordinate of the atom
	 * @param atom id of the atom
	 */
	void clear() {
		for (auto& c : data) {
            c.objects_count = 0;
        }
	}
};
