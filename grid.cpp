#include <cassert>
#include <cstdio>
#include "grid.hpp"

//Grid

template<typename T> Grid<T>::Grid(int width, int height) {
	_size_x=width*2;
	_size_y=height*2;
	_tab=new T[_size_x*_size_y];
	_width=width;
	_height=height;
	_x=_width/2;
	_y=_height/2;
}
template<typename T> Grid<T>::~Grid() {
	delete[] _tab;
}

template<typename T> int Grid<T>::get_width() const {
	return _width;
}
template<typename T> int Grid<T>::get_height() const {
	return _height;
}

template<typename T> void Grid<T>::add_row_before() {
	if(_y>0) { --_y; ++_height; }
	else throw;
}
template<typename T> void Grid<T>::add_row_after() {
	if(_y+_height<_size_y) { ++_y; ++_height; }
	else throw;
}

template<typename T> void Grid<T>::add_col_before() {
	if(_x>0) { --_x; ++_width; }
	else throw;
}
template<typename T> void Grid<T>::add_col_after() {
	if(_x+_width<_size_x) { ++_x; ++_width; }
	else throw;
}

template<typename T> void Grid<T>::del_row_before() {
	if(_height>0 && _y+_height<_size_y) { ++_y; --_height; }
	else throw;
}
template<typename T> void Grid<T>::del_row_after() {
	if(_height>0) { --_height; }
}

template<typename T> void Grid<T>::del_col_before() {
	if(_width>0 && _x+_width<_size_x) { ++_x; --_width; }
}
template<typename T> void Grid<T>::del_col_after() {
	if(_width>0) { --_width; }
}

template<typename T> void Grid<T>::init() {
	for(int i=_y;i<_y+_height;i++) {
		for(int j=_x;j<_x+_width;j++) {
			_tab[get_index(i,j)]=T(0);
		}
	}
}
template<typename T> void Grid<T>::init_full() {
	for(int i=0;i<_size_y;i++) {
		for(int j=0;j<_size_x;j++) {
			_tab[get_index_full(i,j)]=T(0);
		}
	}
}

template<typename T> bool Grid<T>::check_validity() const {
	bool res=(_x>=0 && _y>=0 && _width>=0 && _height>=0 && _size_x>=0 && _size_y>=0);
	res&=(_x+_width<_size_x && _y+_height<_size_y);
	return res;
}
template<typename T> bool Grid<T>::check_middle() const {
	bool res=true;
	res&=( (_size_x%2==0 && _width*2  ==_size_x) || (_size_x%2==1 && _width*2+1==_size_x) );
	res&=( (_size_y%2==0 && _height*2  ==_size_y) || (_size_y%2==1 && _height*2+1==_size_y) );
	res&=(_x*2==_width && _y*2==_height);
	return res;
}

template<typename T> int Grid<T>::get_index(const int row, const int col) const {
	assert(row>=0 && col>=0);
	assert(_y+row<_size_y && _x+col<_size_x);
	return ( (_y+row)*_size_x + (_x+col) );
}
template<typename T> int Grid<T>::get_index_full(const int row, const int col) const {
	assert(row>=0 && col>=0);
	assert(row<_size_y && col<_size_x);
	return ( (row)*_size_x + (col) );
}

template<typename T> const T& Grid<T>::get_cell(const int row, const int col) const {
	return _tab[get_index(row, col)];
}
template<typename T> T& Grid<T>::get_cell(const int row, const int col) {
	return _tab[get_index(row, col)];
}
template<typename T> void Grid<T>::set_cell(const int row, const int col, const T& val) {
	_tab[get_index(row, col)]=val;
}

template<typename T> void Grid<T>::resize_2_1() {
	int x=_x+_width/2;
	int y=_y+_height/2;
	int size_x=_size_x*2;
	int size_y=_size_y*2;
	T* tab=new T[size_x*size_y];
	for(int i=0;i<_height;i++) {
		for(int j=0;j<_width;j++) {
			int oldval=get_cell(i, j);
			tab[ (i+y)*size_x + (j+x) ]=oldval;
		}
	}
	_size_x=size_x;
	_size_y=size_y;
	_x=x;
	_y=y;
	delete[] _tab;
	_tab=tab;
}
template<typename T> void Grid<T>::resize_1_2() {
	int x=_width/2;
	int y=_height/2;
	int size_x=_size_x/2+1;
	int size_y=_size_y/2+1;
	assert(_width<=size_x && _height<=size_y);
	T* tab=new T[size_x*_size_y];
	for(int i=0;i<_height;i++) {
		for(int j=0;j<_width;j++) {
			int oldval=get_cell(i, j);
			tab[ (i+y)*size_x + (j+x) ]=oldval;
		}
	}
	_size_x=size_x;
	_size_y=size_y;
	_x=x;
	_y=y;
	delete[] _tab;
	_tab=tab;
}

template<typename T> const Grid_row_ref_const<T> Grid<T>::operator[](const int row) const {
	return Grid_row_ref_const<T>(this, row);
}
template<typename T> Grid_row_ref<T> Grid<T>::operator[](const int row) {
	return Grid_row_ref<T>(this, row);
}

//Grid_row_ref

template<typename T> Grid_row_ref<T>::Grid_row_ref(Grid_type<T>* pt, int row): _pt(pt), _row(row) {
	//
}
template<typename T> T& Grid_row_ref<T>::operator[](int col) {
	return _pt->get_cell(_row, col);
}
template<typename T> const T& Grid_row_ref<T>::operator[](int col) const {
	return _pt->get_cell(_row, col);
}

//Grid_row_ref_const

template<typename T> Grid_row_ref_const<T>::Grid_row_ref_const(const Grid_type<T>* pt, int row): _pt(pt), _row(row) {
	//
}
template<typename T> const T& Grid_row_ref_const<T>::operator[](int col) const {
	return _pt->get_cell(_row, col);
}

//
