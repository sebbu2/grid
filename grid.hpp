#ifndef GRID_HPP
#define GRID_HPP

template<typename T> class Grid_type {
public:
	virtual int get_width() const=0;
	virtual int get_height() const=0;
	virtual void add_row_before()=0;
	virtual void add_row_after()=0;
	virtual void add_col_before()=0;
	virtual void add_col_after()=0;
	virtual void del_row_before()=0;
	virtual void del_row_after()=0;
	virtual void del_col_before()=0;
	virtual void del_col_after()=0;
	virtual void init()=0;
	virtual void init_full()=0;
	virtual const T& get_cell(const int row, const int col) const=0;
	virtual T& get_cell(const int row, const int col)=0;
	virtual void set_cell(const int row, const int col, const T& val)=0;
};

template<typename T> class Grid_row_ref {
private:
	Grid_type<T>* _pt;
	const int _row;
public:
	Grid_row_ref(Grid_type<T> *pt, const int row);
	T& operator[](const int col);
	const T& operator[](const int col) const;
};

template<typename T> class Grid_row_ref_const {
private:
	const Grid_type<T>* _pt;
	const int _row;
public:
	Grid_row_ref_const(const Grid_type<T>* pt, const int row);
	const T& operator[](const int col) const;
};

template<typename T> class Grid : public Grid_type<T> {
private:
	T* _tab;
	int _x;
	int _y;
	int _width;
	int _height;
	int _size_x;
	int _size_y;
	Grid& operator=(const Grid&);
	Grid(const Grid&);
	int get_index(const int row, const int col) const;
	int get_index_full(const int row, const int col) const;
public:
	virtual int get_width() const;
	virtual int get_height() const;
	virtual void add_row_before();
	virtual void add_row_after();
	virtual void add_col_before();
	virtual void add_col_after();
	virtual void del_row_before();
	virtual void del_row_after();
	virtual void del_col_before();
	virtual void del_col_after();
	virtual void init();
	virtual void init_full();
	virtual bool check_validity() const;
	virtual bool check_middle() const;
	virtual void resize_2_1();
	virtual void resize_1_2();
	virtual const T& get_cell(const int row, const int col) const;
	virtual T& get_cell(const int row, const int col);
	virtual void set_cell(const int row, const int col, const T& val);
	//added
	const Grid_row_ref_const<T> operator[](const int row) const;
	Grid_row_ref<T> operator[](const int row);
public:
	Grid(int width, int height);
	~Grid();
};

#endif
//
