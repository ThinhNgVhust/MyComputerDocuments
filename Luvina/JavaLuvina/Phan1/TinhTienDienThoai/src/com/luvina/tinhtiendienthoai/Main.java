package com.luvina.tinhtiendienthoai;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("\t\tNhap vao ban phim so phut: ");
		Scanner sc = new Scanner(System.in);
		int minutes = sc.nextInt();
		sc.nextLine();
		if (minutes <= 200 && minutes >= 0) {
			System.out.println("Gia cuoc dien thoai la: " + (27000 + minutes * 120) + "d");
		} else if (minutes <= 400 && minutes >= 201) {
			System.out.println("Gia cuoc dien thoai la: " + (27000 + minutes * 80) + "d");
		} else {
			System.out.println("Gia cuoc dien thoai la: " + (27000 + minutes * 40) + "d");
		}

	}

}
