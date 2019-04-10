package com.luvina.pheptoanso;

public class Main {
	public static void main(String[] args) {
		int sum = 0;
		int sumSquare = 0;
		// in for loop ways
		for (int i = 1; i <= 100; i++) {
			sum += i;
			sumSquare += i * i;
		}
		System.out.println("Sum = " + sum);
		sum = 0;
		System.out.println("Sum of Square = " + sumSquare);
		sumSquare = 0;
		// modify
		// stop when times = 50;
		System.out.println("-----------------------------");
		for (int i = 1; i <= 100; i++) {
			sum += i;
			sumSquare += i * i;
			if (i == 50)
				break;
		}
		System.out.println("Sum of first 50 numbers = " + sum);
		sum = 0;
		System.out.println("Sum of Square of first 50 numbers = " + sumSquare);
		sumSquare = 0;
		System.out.println("-----------------------------------");
		for (int i = 1; i <= 100; i++) {
			if (i == 70)
				continue;
			sum += i;
			sumSquare += i * i;
		}
		System.out.println("Sum of first 100 numbers(not include 70) = " + sum);
		sum = 0;
		System.out.println("Sum of Square of first 100 numbers(not include 70) = " + sumSquare);
	}
}
