#include "ultralight_java/util/util.hpp"

#include "ultralight_java/ultralight_java_instance.hpp"

namespace ultralight_java {
    ultralight::String16 Util::create_utf16_from_jstring(JNIEnv *env, jstring str) {
        // Acquire the UTF16 chars of the String and its length
        const jchar *chars = env->GetStringChars(str, nullptr);
        size_t char_count = env->GetStringLength(str);

        // Copy the string
        ultralight::String16 converted(chars, char_count);

        // Release the string chars to prevent memory leaks
        env->ReleaseStringChars(str, chars);

        return converted;
    }

    jstring Util::create_jstring_from_utf16(JNIEnv *env, const ultralight::String16 &str) {
        // Acquire the UTF16 chars of the String and its length
        const jchar *chars = str.udata();
        size_t char_count = str.length();

        // Create the string
        return env->NewString(chars, char_count);
    }

    ultralight::IntRect Util::create_int_rect_from_jobject(JNIEnv *env, jobject object) {
        // Extract the single fields
        int left = env->GetIntField(object, runtime.int_rect.left_field);
        int top = env->GetIntField(object, runtime.int_rect.top_field);
        int right = env->GetIntField(object, runtime.int_rect.right_field);
        int bottom = env->GetIntField(object, runtime.int_rect.bottom_field);

        // Create the IntRect
        return ultralight::IntRect{left, top, right, bottom};
    }

    jobject Util::create_jobject_from_int_rect(JNIEnv *env, const ultralight::IntRect &int_rect) {
        return env->NewObject(
                runtime.int_rect.clazz,
                runtime.int_rect.bounds_constructor,
                int_rect.left,
                int_rect.top,
                int_rect.right,
                int_rect.bottom
        );
    }

    ultralight::KeyEvent Util::create_key_event_from_jobject(JNIEnv *env, jobject event) {
        const auto &t = runtime.ultralight_key_event;

        auto java_event_type = env->GetObjectField(event, t.type_field);
        if (!java_event_type) {
            env->ThrowNew(runtime.null_pointer_exception.clazz, "eventType can't be null");
            return ultralight::KeyEvent{};
        }

        ultralight::KeyEvent::Type event_type;
        if (!runtime.ultralight_key_event_type.constants.from_java(env, java_event_type, &event_type)) {
            return ultralight::KeyEvent{};
        }

        unsigned modifiers = env->GetIntField(event, t.modifiers_field);

        auto java_virtual_key_code = env->GetObjectField(event, t.virtual_key_code_field);
        int virtual_key_code;
        if (!java_virtual_key_code) {
            virtual_key_code = ultralight::KeyCodes::GK_UNKNOWN;
        } else {
            virtual_key_code = env->GetIntField(java_virtual_key_code, runtime.ultralight_key.id_field);
        }

        int native_key_code = env->GetIntField(event, t.native_key_code_field);

        auto java_key_identifier = env->GetObjectField(event, t.key_identifier_field);
        ultralight::String key_identifier;
        if (!java_key_identifier) {
            key_identifier = "";
        } else {
            key_identifier = create_utf16_from_jstring(env, reinterpret_cast<jstring>(java_key_identifier));
        }

        auto java_text = env->GetObjectField(event, t.text_field);
        ultralight::String text;
        if (!java_text) {
            text = "";
        } else {
            text = create_utf16_from_jstring(env, reinterpret_cast<jstring>(java_text));
        }

        auto java_unmodified_text = env->GetObjectField(event, t.unmodified_text_field);
        ultralight::String unmodified_text;
        if (!java_unmodified_text) {
            unmodified_text = "";
        } else {
            unmodified_text = create_utf16_from_jstring(env, reinterpret_cast<jstring>(java_unmodified_text));
        }

        bool is_keypad = env->GetBooleanField(event, t.is_keypad_field);
        bool is_auto_repeat = env->GetBooleanField(event, t.is_auto_repeat_field);
        bool is_system_key = env->GetBooleanField(event, t.is_system_key_field);

        ultralight::KeyEvent out;
        out.type = event_type;
        out.modifiers = modifiers;
        out.virtual_key_code = virtual_key_code;
        out.native_key_code = native_key_code;
        out.key_identifier = key_identifier;
        out.text = text;
        out.unmodified_text = unmodified_text;
        out.is_keypad = is_keypad;
        out.is_auto_repeat = is_auto_repeat;
        out.is_system_key = is_system_key;

        return std::move(out);
    }

    ultralight::MouseEvent Util::create_mouse_event_from_jobject(JNIEnv *env, jobject event) {
        const auto &t = runtime.ultralight_mouse_event;

        auto java_type = env->GetObjectField(event, t.type_field);
        if (!java_type) {
            env->ThrowNew(runtime.null_pointer_exception.clazz, "type can't be null");
            return ultralight::MouseEvent{};
        }

        ultralight::MouseEvent::Type type;
        if (!runtime.ultralight_mouse_event_type.constants.from_java(env, java_type, &type)) {
            return ultralight::MouseEvent{};
        }

        int x = env->GetIntField(event, runtime.ultralight_mouse_event.x_field);
        int y = env->GetIntField(event, runtime.ultralight_mouse_event.y_field);

        auto java_button = env->GetObjectField(event, runtime.ultralight_mouse_event.button_field);

        ultralight::MouseEvent::Button button;
        if (!java_button) {
            button = ultralight::MouseEvent::Button::kButton_None;
        } else {
            if (!runtime.ultralight_mouse_event_button.constants.from_java(env, java_button, &button)) {
                return ultralight::MouseEvent{};
            }
        }

        return ultralight::MouseEvent{type, x, y, button};
    }

    ultralight::ScrollEvent Util::create_scroll_event_from_jobject(JNIEnv *env, jobject event) {
        const auto &t = runtime.ultralight_scroll_event;

        auto java_type = env->GetObjectField(event, t.type_field);
        if (!java_type) {
            env->ThrowNew(runtime.null_pointer_exception.clazz, "type can't be null");
            return ultralight::ScrollEvent{};
        }

        ultralight::ScrollEvent::Type type;
        if (!runtime.ultralight_scroll_event_type.constants.from_java(env, java_type, &type)) {
            return ultralight::ScrollEvent{};
        }

        int delta_x = env->GetIntField(event, t.delta_x_field);
        int delta_y = env->GetIntField(event, t.delta_y_field);

        return ultralight::ScrollEvent{type, delta_x, delta_y};
    }
}