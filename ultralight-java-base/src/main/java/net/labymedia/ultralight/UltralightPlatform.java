package net.labymedia.ultralight;

import net.labymedia.ultralight.annotation.NativeCall;
import net.labymedia.ultralight.annotation.NativeType;
import net.labymedia.ultralight.annotation.Unsigned;
import net.labymedia.ultralight.config.UltralightConfig;
import net.labymedia.ultralight.ffi.ObjectWithHandle;
import net.labymedia.ultralight.plugin.clipboard.UltralightClipboard;
import net.labymedia.ultralight.plugin.filesystem.UltralightFileSystem;
import net.labymedia.ultralight.plugin.logging.UltralightLogger;

/**
 * Platform singleton to configure Ultralight and provide user-defined implementations for various platform operations.
 * <p>
 * All of these settings and user-defined interfaces should be set BEFORE creating the Renderer.
 */
@NativeType("ultralight::Platform")
public class UltralightPlatform implements ObjectWithHandle {
    /**
     * This fields holds a pointer to the underlying instance of the C++ object.
     */
    @NativeType("ultralight::Platform *")
    @Unsigned
    private final long handle;

    @NativeCall
    private UltralightPlatform(long handle) {
        this.handle = handle;
    }

    /**
     * Get the {@link UltralightPlatform} singleton.
     *
     * @return The {@link UltralightPlatform} singleton
     */
    public static native UltralightPlatform instance();

    /**
     * Set the Config.
     *
     * @param config The new config
     */
    public native void setConfig(UltralightConfig config);

    /**
     * Sets the internal font loader implementation to the platform dependent one.
     */
    public native void usePlatformFontLoader();

    /**
     * Sets the internal file system implementation to the platform dependent one.
     *
     * @param basePath The path to resolve `file:///` URL's relative to
     */
    public native void usePlatformFileSystem(String basePath);

    /**
     * Set the File System (will be used for all file system operations).
     *
     * @param fileSystem The file system to use
     */
    public native void setFileSystem(UltralightFileSystem fileSystem);

    /**
     * Set the Clipboard (will be used for all clipboard operations).
     *
     * @param clipboard A user-defined Clipboard implementation
     */
    public native void setClipboard(UltralightClipboard clipboard);

    // TODO: Font loader support

    // TODO: GPU driver support

    // TODO: Surface factory support

    /**
     * Sets the internal logger implementation to the provided one.
     *
     * @param logger The logger to use
     */
    public native void setLogger(UltralightLogger logger);

    /**
     * Retrieves the native underlying pointer to the Platform object.
     *
     * @return The native underlying pointer
     */
    @Override
    public @NativeType("ultralight::Platform *") @Unsigned long getHandle() {
        return handle;
    }
}