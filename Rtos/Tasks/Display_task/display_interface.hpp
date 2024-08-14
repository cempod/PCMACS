#pragma once

#include <stdint.h>

enum USB_STATUS{
    USB_OK = 0,
    USB_DISCONNECTED
};

void interface_init(void);

class LoadMeter {
    private:
        int load;
        lv_obj_t * arc;
        lv_anim_t arc_anim;
        static void animation_callback(void * obj, int32_t v) {
            lv_arc_set_value((lv_obj_t *)obj, v);
        }
    public:
        LoadMeter(int x_offset, int y_offset, int size);
        void set_load(int val);
        void set_rotation(int val);
        void set_angles(int a, int b);
        void set_reverse(bool rev);
};

class LabelLine {
    private:
        lv_style_t style_line;
        lv_obj_t * line_l;

    public:
    LabelLine(lv_point_precise_t* points, int num);
    void set_offsets(int x_offset, int y_offset);
};

class Label {
    private:
    lv_obj_t * label;
    char str[20];

    public:
    Label(int x_offset, int y_offset, const lv_font_t * font);
    void set_text(const char* msg, ...);
};