/*
 * Ultralight Java - Java wrapper for the Ultralight web engine
 * Copyright (C) 2020 LabyMedia and contributors
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

package com.labymedia.ultralight.plugin.render;

import com.labymedia.ultralight.annotation.NativeType;
import com.labymedia.ultralight.math.IntRect;

@NativeType("ultralight::GPUState")
public class UltralightGPUState {
    public final @NativeType("uint32_t")
    long viewportWidth, viewportHeight;

    public final @NativeType("ultralight::Matrix4x4")
    float[] transformMatrix;

    public final @NativeType("bool")
    boolean enableTexturing, enableBlend;

    public final @NativeType("uint8_t")
    short shaderType;

    public final @NativeType("uint32_t")
    long renderBufferId, texture1Id, texture2Id, texture3Id;

    public final @NativeType("float[]")
    float[] uniformScalar;
    public final @NativeType("ultralight::vec4[]")
    float[][] uniformVector;
    public final @NativeType("uint8_t")
    short clipSize;
    public final @NativeType("ultralight::Matrix4x4[]")
    float[][] clip;

    public final @NativeType("bool")
    boolean enableScissor;

    public final @NativeType("IntRect")
    IntRect scissorRect;

    public UltralightGPUState(long viewportWidth, long viewportHeight, float[] transformMatrix, boolean enableTexturing, boolean enableBlend, short shaderType, long renderBufferId, long texture1Id, long texture2Id, long texture3Id, float[] uniformScalar, float[][] uniformVector, short clipSize, float[][] clip, boolean enableScissor, IntRect scissorRect) {
        this.viewportWidth = viewportWidth;
        this.viewportHeight = viewportHeight;
        this.transformMatrix = transformMatrix;
        this.enableTexturing = enableTexturing;
        this.enableBlend = enableBlend;
        this.shaderType = shaderType;
        this.renderBufferId = renderBufferId;
        this.texture1Id = texture1Id;
        this.texture2Id = texture2Id;
        this.texture3Id = texture3Id;
        this.uniformScalar = uniformScalar;
        this.uniformVector = uniformVector;
        this.clipSize = clipSize;
        this.clip = clip;
        this.enableScissor = enableScissor;
        this.scissorRect = scissorRect;
    }
}
