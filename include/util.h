#pragma once

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

struct NumInfo
{
	int n_digits;
	double dec;
	int exp;
};

struct Param2Px
{

	Param2Px(double _x0, double _y0, double _x1, double _y1)
	{
		x0 = _x0;
		y0 = _y0;
		wx = _x1 - _x0;
		wy = _y1 - _y0;
	}

	double wx, wy, x0, y0;

	double x(double t) { return x0 + t * wx; };
	double y(double t) { return y0 + (1-t)*wy; };

	std::tuple<double, double>  operator()(double tx, double ty) { return std::tuple<double, double>(x(tx), y(ty)); };
};

template<typename T>
static T interp1(const T& a, const T& b, const T& t)
{
	return a + t * (b - a);
}

template<typename T>
static std::vector<T> interp1(const T& a, const T& b, const std::vector<T>& t)
{
	std::vector<T> r(t.size());
	for (size_t i = 0; i < t.size(); i++)
	{
		r[i] = interp1(a, b, t[i]);
	}
	return r;
}

static NumInfo scientific_notation(double num)
{

	NumInfo info;
	if (num == 0) {
		info.dec = 0;
		info.n_digits = 1;
		info.exp = 0;
		return info;
	}

	bool is_negative = num < 0;
	num = abs(num);

	int n_digits = 1;
	int exponent = 0;
	while (num >= 10) {
		num /= 10;
		n_digits++;
		exponent++;
	}
	while (num < 1) {
		num *= 10;
		n_digits++;
		exponent--;
	}
	
	info.dec = num;
	info.dec = num;
	info.exp = exponent;

	return info;
}

static int number_of_lines(const fs::path& file)
{
	std::ifstream in(file);

	// Check buffer size
	in.seekg(0, in.end);
	int buffer_size = (int)in.tellg();
	in.seekg(0, in.beg);

	// Read file to memory
	char* text = new char[buffer_size];
	in.read(text, buffer_size);

	// Count number of lines
	int num_lines = 0;
	for (int i = 0; i < buffer_size; i++)
	{
		if (text[i] == '\n')
			num_lines++;
	}

	return num_lines;
}

static void readXYZFile(fs::path& filepath, std::vector<double>& x, std::vector<double>& y, std::vector<double>& z)
{
	std::ifstream in(filepath);
	int nol = number_of_lines(filepath);
	x.resize(nol);
	y.resize(nol);
	z.resize(nol);
	for (int n = 0; n < nol; n++)
		in >> x[n] >> y[n] >> z[n];
	in.close();
}

static std::vector<std::vector<double>> matrix_real(int m, int n)
{
	std::vector<std::vector<double>> M(m);
	for (int i = 0; i < m; i++)
	{
		M[i] = std::vector<double>(n);
	}
	return M;
}

static std::vector<std::vector<double>> reshape_mtx(std::vector<double>& x, int rows, int cols)
{
	
	std::vector<std::vector<double>> X = matrix_real(rows,cols);

	int idx = 0;
	for (int n = 0; n < cols; n++)
	{
		for (int m = 0; m < rows; m++)
		{
			X[m][n] = x[idx];
			idx++;
		}
	}

	return X;

}

static std::vector<std::vector<double>> reshape_mtx_t(std::vector<double>& x, int rows, int cols)
{
	
	std::vector<std::vector<double>> X = matrix_real(rows,cols);

	int idx = 0;
	for (int m = 0; m < rows; m++)
	{
		for (int n = 0; n < cols; n++)
		{
			X[m][n] = x[idx];
			idx++;
		}
	}

	return X;

}
