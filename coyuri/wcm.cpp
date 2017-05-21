#include "prot.hpp"
#include "values.hpp"
#include <iostream>
#include <cmath>

/*
*wcm�֐����ł͒ʏ�̏����̔Ֆʂ𑀍삷�銴���ōs��
*/

//�������Ȃ�wcm�֐�
std::vector<Point> null_wcm(Point p) {
	std::vector<Point> points;
	return points;
}

//����wcm�֐�
std::vector<Point> hu_wcm(Point point) {
	std::vector<Point> points;

	/*
	*��O�����m�F
	*/
	jands_one_wcm(point.get_x(), point.get_y() - 1, &points);

	return points;
}

std::vector<Point> kyousha_wcm(Point point) {
	std::vector<Point> points;
	int y = point.get_y() - 1;
	while (jands_one_wcm(point.get_x(), y, &points)) {
		y--;
	}
	return points;
}

//�j�n��wcm�֐�
std::vector<Point> keima_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�Q�O�ɐi�߂Ȃ��ʒu�ɂ���ꍇ�ړ��ł��Ȃ�
	*/
	if (p.get_y() <= 2) return points;

	if (can_target(p.get_x() + 1, p.get_y() - 2))
		points.push_back(Point(p.get_x() + 1, p.get_y() - 2));

	if (can_target(p.get_x() - 1, p.get_y() - 2))
		points.push_back(Point(p.get_x() - 1, p.get_y() - 2));

	return points;
}

//���wcm�֐�
std::vector<Point> gin_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�O�������̈ړ��\����
	*/
	jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	jands_one_wcm(p.get_x(), p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	/*
	*��������̈ړ��\����
	*/
	jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}

//���wcm�֐�
std::vector<Point> kin_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�O�������̈ړ��\����
	*/
	jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	jands_one_wcm(p.get_x(), p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	/*
	*�������̈ړ��\����
	*/
	jands_one_wcm(p.get_x() - 1, p.get_y(), &points);
	jands_one_wcm(p.get_x() + 1, p.get_y(), &points);

	/*
	*��������̈ړ��\����
	*/
	jands_one_wcm(p.get_x(), p.get_y() + 1, &points);

	return points;
}

//��Ԃ�wcm�֐�
std::vector<Point> hisha_wcm(Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*�������̈ړ��\����
	*/
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x--;
	}

	/*
	*�������̈ړ��\����
	*/
	x = p.get_x() + 1;
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x++;
	}

	/*
	*�������̈ړ��\����
	*/
	y = p.get_y() + 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y++;
	}

	/*
	*������̈ړ��\����
	*/
	y = p.get_y() - 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y--;
	}

	return points;
}

//�p��wcm�֐�
std::vector<Point> kaku_wcm(Point p) {
	std::vector<Point> points;

	int x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*�E������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*��������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y++;
	}

	return points;
}

//������wcm�֐�
std::vector<Point> ou_wcm(Point p) {
	std::vector<Point> points;

	//�O�������̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	//�������̈ړ��\����
	jands_one_wcm(p.get_x() + 1, p.get_y(), &points);
	jands_one_wcm(p.get_x() - 1, p.get_y(), &points);

	//��������̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() + 1, &points);
	jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}

//����wcm�֐�
std::vector<Point> ryu_wcm(Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*�������̈ړ��\����
	*/
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x--;
	}

	/*
	*�������̈ړ��\����
	*/
	x = p.get_x() + 1;
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x++;
	}

	/*
	*�������̈ړ��\����
	*/
	y = p.get_y() + 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y++;
	}

	/*
	*������̈ړ��\����
	*/
	y = p.get_y() - 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y--;
	}

	//�΂ߏ�����̈ړ��\����
	jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	//�΂߉������̈ړ��\����
	jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}

//�n��wcm�֐�
std::vector<Point> uma_wcm(Point p) {
	std::vector<Point> points;

	int x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*�E������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*��������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y++;
	}

	//�������̈ړ��\����
	jands_one_wcm(p.get_x() + 1, p.get_y(), &points);
	jands_one_wcm(p.get_x() - 1, p.get_y(), &points);

	//�O���̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() - 1, &points);

	//��������̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() + 1, &points);

	return points;
}


//�G�̕���wcm�֐�
std::vector<Point> en_hu_wcm(Point point) {
	std::vector<Point> points;

	/*
	*��O�����m�F
	*/
	ai_jands_one_wcm(point.get_x(), point.get_y() + 1, &points);

	return points;
}

//�G�̍��Ԃ�wcm�֐�
std::vector<Point> en_kyousha_wcm(Point point) {
	std::vector<Point> points;
	int y = point.get_y() + 1;
	while (ai_jands_one_wcm(point.get_x(), y, &points)) {
		y++;
	}
	return points;
}

//�G�̌j�n��wcm�֐�
std::vector<Point> en_keima_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�Q�O�ɐi�߂Ȃ��ʒu�ɂ���ꍇ�ړ��ł��Ȃ�
	*/
	if (p.get_y() >= 8) return points;

	if (ai_can_target(p.get_x() + 1, p.get_y() + 2))
		points.push_back(Point(p.get_x() + 1, p.get_y() + 2));

	if (ai_can_target(p.get_x() - 1, p.get_y() + 2))
		points.push_back(Point(p.get_x() - 1, p.get_y() + 2));

	return points;
}

//�G�̋��wcm�֐�
std::vector<Point> en_gin_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�O�������̈ړ��\����
	*/
	ai_jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x(), p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	/*
	*��������̈ړ��\����
	*/
	ai_jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	return points;
}

//�G�̋���wcm�֐�
std::vector<Point> en_kin_wcm(Point p) {
	std::vector<Point> points;

	/*
	*�O�������̈ړ��\����
	*/
	ai_jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x(), p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	/*
	*�������̈ړ��\����
	*/
	ai_jands_one_wcm(p.get_x() - 1, p.get_y(), &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y(), &points);

	/*
	*��������̈ړ��\����
	*/
	ai_jands_one_wcm(p.get_x(), p.get_y() - 1, &points);

	return points;
}

//�G�̔�Ԃ�wcm�֐�
std::vector<Point> en_hisha_wcm(Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*�������̈ړ��\����
	*/
	while (ai_jands_one_wcm(x, p.get_y(), &points)) {
		x--;
	}

	/*
	*�������̈ړ��\����
	*/
	x = p.get_x() + 1;
	while (ai_jands_one_wcm(x, p.get_y(), &points)) {
		x++;
	}

	/*
	*�������̈ړ��\����
	*/
	y = p.get_y() - 1;
	while (ai_jands_one_wcm(p.get_x(), y, &points)) {
		y--;
	}

	/*
	*������̈ړ��\����
	*/
	y = p.get_y() + 1;
	while (ai_jands_one_wcm(p.get_x(), y, &points)) {
		y++;
	}

	return points;
}

//�G�̊p��wcm�֐�
std::vector<Point> en_kaku_wcm(Point p) {
	std::vector<Point> points;

	int x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*�E������̈ړ��\����
	*/
	while (ai_jands_one_wcm(x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*��������̈ړ��\����
	*/
	while (ai_jands_one_wcm(x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (ai_jands_one_wcm(x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (ai_jands_one_wcm(x, y, &points)) {
		x++;
		y++;
	}

	return points;
}

//�G�̉�����wcm�֐�
std::vector<Point> en_ou_wcm(Point p) {
	std::vector<Point> points;

	//�O�������̈ړ��\����
	ai_jands_one_wcm(p.get_x(), p.get_y() - 1, &points);
	ai_jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	//�������̈ړ��\����
	ai_jands_one_wcm(p.get_x() + 1, p.get_y(), &points);
	ai_jands_one_wcm(p.get_x() - 1, p.get_y(), &points);

	//��������̈ړ��\����
	ai_jands_one_wcm(p.get_x(), p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	ai_jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}


//����wcm�֐�
std::vector<Point> en_ryu_wcm(Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*�������̈ړ��\����
	*/
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x--;
	}

	/*
	*�������̈ړ��\����
	*/
	x = p.get_x() + 1;
	while (jands_one_wcm(x, p.get_y(), &points)) {
		x++;
	}

	/*
	*�������̈ړ��\����
	*/
	y = p.get_y() + 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y++;
	}

	/*
	*������̈ړ��\����
	*/
	y = p.get_y() - 1;
	while (jands_one_wcm(p.get_x(), y, &points)) {
		y--;
	}

	//�΂ߏ�����̈ړ��\����
	jands_one_wcm(p.get_x() - 1, p.get_y() - 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() - 1, &points);

	//�΂߉������̈ړ��\����
	jands_one_wcm(p.get_x() - 1, p.get_y() + 1, &points);
	jands_one_wcm(p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}

//�n��wcm�֐�
std::vector<Point> en_uma_wcm(Point p) {
	std::vector<Point> points;

	int x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*�E������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*��������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*�E�������̈ړ��\����
	*/
	while (jands_one_wcm(x, y, &points)) {
		x++;
		y++;
	}

	//�������̈ړ��\����
	jands_one_wcm(p.get_x() + 1, p.get_y(), &points);
	jands_one_wcm(p.get_x() - 1, p.get_y(), &points);

	//�O���̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() - 1, &points);

	//��������̈ړ��\����
	jands_one_wcm(p.get_x(), p.get_y() + 1, &points);

	return points;

}

//����wcm�֐�
std::vector<Point> tegoma_wcm(Point p) {
	std::vector<Point> points;
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			if (main_ban[x][y] == EMPTY)
				points.push_back(Point(std::abs(x - 9), y + 1));
	return points;
}

//�łƂ��ɁA����ɂȂ�Ȃ����߂�wcm�֐�
std::vector<Point> nihu_wcm() {
	std::vector<Point> points;
	bool nihu = false;

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (main_ban[x][y] == HU) {
				/*
				*����������
				*/
				nihu = true;
			}
		}
		if (!nihu) {
			/*
			*����������Ȃ��ꍇ�A���̈�s��ǉ�
			*/
			for (int y = 1; y < 9; y++) {
				if (main_ban[x][y] == EMPTY && main_ban[x][y - 1] != EN_OU) {
					points.push_back(Point(std::abs(x - 9), y + 1));
				}
			}
		}
		nihu = false;
	}

	return points;
}

//�łƂ��ɁA����ɂȂ�Ȃ����߂�wcm�֐�(ai�p)
std::vector<Point> ai_nihu_wcm() {
	std::vector<Point> points;
	bool nihu = false;

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (main_ban[x][y] == EN_HU) {
				/*
				*����������
				*/
				nihu = true;
			}
		}
		if (!nihu) {
			/*
			*����������Ȃ��ꍇ�A���̈�s��ǉ�
			*/
			for (int y = 0; y < 8; y++) {
				if (main_ban[x][y] == EMPTY && main_ban[x][y + 1] != OU) {
					points.push_back(Point(std::abs(x - 9), y + 1));
				}
			}
		}
		nihu = false;
	}

	return points;
}
