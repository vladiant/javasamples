package com.example;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Part 1: Simple JNI Wrapper ===");

        // Create multiple native objects
        NativeClass nc1 = new NativeClass();
        NativeClass nc2 = new NativeClass();

        System.out.println("Calling fun() on nc1:");
        nc1.fun();

        System.out.println("Calling fun() on nc2:");
        nc2.fun();

        System.out.println("Done.");
    }
}
