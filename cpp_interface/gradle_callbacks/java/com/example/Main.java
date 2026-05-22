package com.example;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Part 2: Callbacks from Native ===");

        NativeClass nc = new NativeClass();

        nc.setListener(new NativeListener() {
            @Override
            public void print(String msg) {
                System.out.println("[Java callback] " + msg);
            }
        });

        // Run scan in a separate thread since it blocks
        Thread scanThread = new Thread(() -> {
            nc.scan();
        });
        scanThread.start();

        // Let it run for 5 seconds, then stop
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Stopping scan...");
        nc.stop();

        try {
            scanThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Done.");
    }
}
