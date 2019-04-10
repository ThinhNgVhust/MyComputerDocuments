package com.luvina.xeploaihocsinh;

import java.util.Scanner;

public class Main {
	private static final int DIEM_10 = 10;
	private static final int DIEM_9 = 9;
	private static final int DIEM_8 = 8;
	private static final int DIEM_7 = 7;
	private static final int DIEM_6 = 6;
	private static final int DIEM_5 = 5;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Nhap vap diem trung binh cua hoc sinh: ");
		Scanner scanner = new Scanner(System.in);
		int diem = scanner.nextInt();
		scanner.nextLine();
		switch (diem) {
		case DIEM_10:
		case DIEM_9:
			System.out.println("Xep loai gioi");
			break;
		case DIEM_8:
		case DIEM_7:
			System.out.println("Xep loai kha");
			break;
		case DIEM_6:
		case DIEM_5:
			System.out.println("Xep loai trung binh");
			break;
		default:
			System.out.println("Xep loai yeu");
			break;
		}
	}

}
