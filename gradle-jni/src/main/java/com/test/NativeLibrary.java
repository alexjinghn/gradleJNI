package com.test;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;


final class NativeLibrary {
    private static final boolean DEBUG = true;
    private static final String PACKAGENAME = "com/test/";
    private static final String LIBNAME = "bridge";

    public static void load() {
        if (isLoaded() || tryLoadLibrary()) {
            // Either:
            // (1) The native library has already been statically loaded, OR
            // (2) The required native code has been statically linked (through a custom launcher), OR
            // (3) The native code is part of another library (such as an an application-level libraryh)
            // that has already been loaded.
            //
            // Doesn't matter how, but it seems the native code is loaded, so nothing else to do.
            return;
        }
        // Native code is not present, perhaps it has been packaged into the .jar file containing this.
        final String resourceName = makeResourceName();
        log("resourceName: " + resourceName);
        final InputStream resource =
                NativeLibrary.class.getClassLoader().getResourceAsStream(resourceName);
        if (resource == null) {
            throw new UnsatisfiedLinkError(
                    String.format(
                            "Cannot find bridge native library for OS: %s, architecture: %s. ",
                            os(), architecture()));
        }
        try {
            System.load(extractResource(resource));
        } catch (IOException e) {
            throw new UnsatisfiedLinkError(
                    String.format(
                            "Unable to extract native library into a temporary file (%s)", e.toString()));
        }
    }

    private static boolean tryLoadLibrary() {
        try {
            System.loadLibrary(LIBNAME);
            return true;
        } catch (UnsatisfiedLinkError e) {
            log("tryLoadLibraryFailed: " + e.getMessage());
            return false;
        }
    }

    private static boolean isLoaded() {
        try {
            JniBridge.version();
            log("isLoaded: true");
            return true;
        } catch (UnsatisfiedLinkError e) {
            return false;
        }
    }

    private static String extractResource(InputStream resource) throws IOException {
        final String sampleFilename = System.mapLibraryName(LIBNAME);
        final int dot = sampleFilename.indexOf(".");
        final String prefix = (dot < 0) ? sampleFilename : sampleFilename.substring(0, dot);
        final String suffix = (dot < 0) ? null : sampleFilename.substring(dot);

        final File dst = File.createTempFile(prefix, suffix);
        final String dstPath = dst.getAbsolutePath();
        dst.deleteOnExit();
        log("extracting native library to: " + dstPath);
        final long nbytes = copy(resource, dst);
        log(String.format("copied %d bytes to %s", nbytes, dstPath));
        return dstPath;
    }

    private static String os() {
        final String p = System.getProperty("os.name").toLowerCase();
        if (p.contains("linux")) {
            return "linux";
        } else if (p.contains("os x") || p.contains("darwin")) {
            return "darwin";
        } else if (p.contains("windows")) {
            return "windows";
        } else {
            return p.replaceAll("\\s", "");
        }
    }

    private static String architecture() {
        final String arch = System.getProperty("os.arch").toLowerCase();
        return (arch.equals("amd64")) ? "x86_64" : arch;
    }

    private static void log(String msg) {
        if (DEBUG) {
            System.err.println("NativeLibrary: " + msg);
        }
    }

    private static String makeResourceName() {
        return PACKAGENAME
                + String.format("%s-%s/", os(), architecture())
                + System.mapLibraryName(LIBNAME);
    }

    private static long copy(InputStream src, File dstFile) throws IOException {
        FileOutputStream dst = new FileOutputStream(dstFile);
        try {
            byte[] buffer = new byte[1 << 20]; // 1MB
            long ret = 0;
            int n = 0;
            while ((n = src.read(buffer)) >= 0) {
                dst.write(buffer, 0, n);
                ret += n;
            }
            return ret;
        } finally {
            dst.close();
            src.close();
        }
    }
}
