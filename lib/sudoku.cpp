#include "sudoku.hpp"

namespace sudoku {
	void free(sudoku *data) {
		delete data->sheet;
		delete data->filename;
		delete data;
	};
};
