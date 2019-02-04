#include "MyMatrix3.h"



MyMatrix3::MyMatrix3() : 
	m11{ 0.0 }, 
	m12{ 0.0 }, 
	m13{ 0.0 }, 
	m21{ 0.0 }, 
	m22{ 0.0 }, 
	m23{ 0.0 }, 
	m31{ 0.0 }, 
	m32{ 0.0 }, 
	m33{ 0.0 }
{
}

MyMatrix3::MyMatrix3(double t_a11, double t_a12, double t_a13, double t_a21, double t_a22, double t_a23, double t_a31, double t_a32, double t_a33):
	m11{ t_a11 },
	m12{ t_a12 },
	m13{ t_a13 },
	m21{ t_a21 },
	m22{ t_a22 },
	m23{ t_a23 },
	m31{ t_a31 },
	m32{ t_a32 },
	m33{ t_a33 }
{
}

MyMatrix3::MyMatrix3(MyVector3 row1, MyVector3 row2, MyVector3 row3) :
	m11{ row1.x },
	m12{ row1.y },
	m13{ row1.z },
	m21{ row2.x },
	m22{ row2.y },
	m23{ row2.z },
	m31{ row3.x },
	m32{ row3.y},
	m33{ row3.z }
{
}


MyMatrix3::~MyMatrix3()
{
}

std::string MyMatrix3::toString() const
{ 
	const std::string output = "[" + std::to_string(m11) + "," + std::to_string(m12) + "," + std::to_string(m13) + "]\n"
							+ "[" + std::to_string(m21) + "," + std::to_string(m22) + "," + std::to_string(m23) + "]\n"
							+ "[" + std::to_string(m31) + "," + std::to_string(m32) + "," + std::to_string(m33) + "]";
	return output;
	
}

bool MyMatrix3::operator==(const MyMatrix3 other) const
{
	return { m11 == other.m11 && m12 == other.m12 && m13 == other.m13
		&& m21 == other.m21 && m22 == other.m22 && m23 == other.m23
		&& m31 == other.m31 && m32 == other.m32 && m33 == other.m33 };
}

bool MyMatrix3::operator!=(const MyMatrix3 other) const
{
	return { m11 != other.m11 || m12 != other.m12 || m13 != other.m13
		|| m21 != other.m21 || m22 != other.m22 || m23 != other.m23
		|| m31 != other.m31 || m32 != other.m32 || m33 != other.m33 };
}

MyMatrix3 MyMatrix3::operator+(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m11 + t_other.m11, m12 + t_other.m12, m13 + t_other.m13,
		m21 + t_other.m21, m22 + t_other.m22, m23 + t_other.m23,
		m31 + t_other.m31, m32 + t_other.m32, m33 + t_other.m33 };
}

MyMatrix3 MyMatrix3::operator-(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m11 - t_other.m11, m12 - t_other.m12, m13 - t_other.m13,
		m21 - t_other.m21, m22 - t_other.m22, m23 - t_other.m23,
		m31 - t_other.m31, m32 - t_other.m32, m33 - t_other.m33 };
}

MyMatrix3 MyMatrix3::operator*(const MyMatrix3 t_other) const
{
	MyMatrix3 answer{};
	answer.m11 = row(0).dot(t_other.column(0));
	answer.m12 = row(0).dot(t_other.column(1));
	answer.m13 = row(0).dot(t_other.column(2));

	answer.m21 = row(1).dot(t_other.column(0));
	answer.m22 = row(1).dot(t_other.column(1));
	answer.m23 = row(1).dot(t_other.column(2));

	answer.m31 = row(2).dot(t_other.column(0));
	answer.m32 = row(2).dot(t_other.column(1));
	answer.m33 = row(2).dot(t_other.column(2));

	return answer;
}

MyVector3 MyMatrix3::operator*(const MyVector3 t_vector) const
{
	return MyVector3{ row(0).dot(t_vector), row(1).dot(t_vector), row(2).dot(t_vector) };
}

MyMatrix3 MyMatrix3::operator*(const double t_scale) const
{
	return MyMatrix3{ m11 * t_scale, m12 * t_scale, m13 * t_scale,
		m21 * t_scale, m22 * t_scale, m23 * t_scale,
		m31 * t_scale, m32 * t_scale, m33 * t_scale };
}

MyMatrix3 MyMatrix3::transpose() const
{
	return MyMatrix3{ m11, m21, m31, m12, m22, m32, m13, m23, m33 };
}

double MyMatrix3::determinant() const
{
	return { m11 * m22 * m33 - m11 * m32 * m23 + m21 * m32 * m13 - m31 * m22 * m13 + m31 * m12 * m23 - m21 * m12 * m33 };
}

MyMatrix3 MyMatrix3::inverse() const
{
	if (determinant() == 0)
		return MyMatrix3{};
	else
	{
		double scale = 1 / determinant();
		MyMatrix3 answer{};
		answer.m11 = scale * (m22 * m33 - m23 * m32);
		answer.m12 = scale * (m13 * m32 - m12 * m33);
		answer.m13 = scale * (m12 * m23 - m13 * m22);

		answer.m21 = scale * (m23 * m31 - m21 * m33);
		answer.m22 = scale * (m11 * m33 - m13 * m31);
		answer.m23 = scale * (m13 * m21 - m11 * m23);

		answer.m31 = scale * (m21 * m32 - m22 * m31);
		answer.m32 = scale * (m12 * m31 - m11 * m32);
		answer.m33 = scale * (m11 * m22 - m12 * m21);

		return answer;
	}
}

MyVector3 MyMatrix3::row(const int t_row) const
{
	switch (t_row)
	{
	case 0:
		return MyVector3{ m11, m12, m13 };
	case 1:
		return MyVector3{ m21, m22, m23 };
	case 2:
		return MyVector3{ m31, m32, m33 };
	}
	return MyVector3{}; // shouldn't get here learn to count from zero
}

MyVector3 MyMatrix3::column(const int t_column) const
{
	switch (t_column)
	{
	case 0:
		return MyVector3{ m11, m21, m31 };
	case 1:
		return MyVector3{ m12, m22, m32 };
	case 2:
		return MyVector3{ m13, m23, m33 };
	}
	return MyVector3();// shouldn't get here learn to count from zero
}

MyMatrix3 MyMatrix3::rotationZ(const double angleRadians)
{
	return MyMatrix3{
		std::cos(angleRadians), -std::sin(angleRadians), 0.0,
		std::sin(angleRadians), std::cos(angleRadians), 0.0,
		0.0, 0.0, 1.0 }	;
}

MyMatrix3 MyMatrix3::rotationY(const double t_angleRadians)
{
	return MyMatrix3{
		std::cos(t_angleRadians), 0.0, std::sin(t_angleRadians),
		0.0 ,1.0 ,0.0,
		-std::sin(t_angleRadians), 0.0, std::cos(t_angleRadians)
	};
}

MyMatrix3 MyMatrix3::rotationX(const double t_angleRadians)
{
	return MyMatrix3{
		1.0 , 0.0 , 0.0,
		0.0 ,std::cos(t_angleRadians) ,-std::sin(t_angleRadians),
		0.0 , std::sin(t_angleRadians), std::cos(t_angleRadians)};
}

MyMatrix3 MyMatrix3::translation(const MyVector3 t_displacement)
{
	return MyMatrix3{
		1.0 , 0.0 , t_displacement.x,
		0.0 , 1.0 , t_displacement.y,
		0.0 , 0.0 , 1.0	};
}

MyMatrix3 MyMatrix3::scale(const double t_scalingfactor)
{
	return MyMatrix3{
		t_scalingfactor, 0.0 , 0.0,
		0.0 ,t_scalingfactor, 0.0,
		0.0 , 0.0 ,1 };
}

