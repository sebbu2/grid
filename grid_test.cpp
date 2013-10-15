#include <cstdio>
#include <cassert>
#include <stdexcept>
#include <exception>
#include <typeinfo>
#include "grid.hpp"

using namespace std;

int main(void) {
	Grid<int> grille(4, 4);

	grille.init_full();

	assert(grille.check_middle());

	Grid_row_ref_const<int> l1(&grille, 0);
	Grid_row_ref<int> l2(&grille, 1);
	Grid_row_ref<int> l3(&grille, 2);
	Grid_row_ref<int> l4(&grille, 3);

	grille[0][0]=1;
	l2[1]=2;
	grille[2][2]=l1[0]*3;
	grille[3][3]=grille[1][1]*2;

	printf("%d %d %d %d\n", l1[0], l1[1], l1[2], l1[3]);
	printf("%d %d %d %d\n", l2[0], l2[1], l2[2], l2[3]);
	printf("%d %d %d %d\n", l3[0], l3[1], l3[2], l3[3]);
	printf("%d %d %d %d\n", l4[0], l4[1], l4[2], l4[3]);

	grille.add_row_before();
	assert(grille.check_validity());
	grille.add_row_before();
	assert(grille.check_validity());

	/*try {
		grille.add_row_before();
	}
	catch (exception& e) {
		printf("3rd add_row_before failed 1.\n");
	}
	catch (...) {
		printf("3rd add_row_before failed 2.\n");
	}//*/

	grille.del_row_before();
	assert(grille.check_validity());
	grille.del_row_before();
	assert(grille.check_validity());

	/*try {
		grille.del_row_before();
	}
	catch(exception& e) {
		printf("3rd del_row_before failed 1.\n");
	}
	catch(...) {
		printf("3rd del_row_before failed 2.\n");
	}//*/

	assert(grille.check_middle());

	grille.resize_2_1();
	assert(grille.check_validity());

	printf("\n");

	printf("%d %d %d %d\n", l1[0], l1[1], l1[2], l1[3]);
	printf("%d %d %d %d\n", l2[0], l2[1], l2[2], l2[3]);
	printf("%d %d %d %d\n", l3[0], l3[1], l3[2], l3[3]);
	printf("%d %d %d %d\n", l4[0], l4[1], l4[2], l4[3]);

	grille.resize_1_2();
	assert(grille.check_validity());

	printf("\n");

	printf("%d %d %d %d\n", l1[0], l1[1], l1[2], l1[3]);
	printf("%d %d %d %d\n", l2[0], l2[1], l2[2], l2[3]);
	printf("%d %d %d %d\n", l3[0], l3[1], l3[2], l3[3]);
	printf("%d %d %d %d\n", l4[0], l4[1], l4[2], l4[3]);

	assert(grille.check_middle());

	return 0;
}
//
