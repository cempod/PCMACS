#include "lvgl.h"
#include "display_interface.hpp"
#include <stdio.h>
#include <stdarg.h>

void interface_init(){
    lv_obj_set_style_bg_color ( lv_screen_active() , lv_palette_darken(LV_PALETTE_GREY,4),0) ;
    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);
}

LoadMeter::LoadMeter(int x_offset, int y_offset, int size) {
    load = 0;
    arc = lv_arc_create(lv_screen_active());
    lv_arc_set_rotation(arc,125);
    lv_arc_set_bg_angles(arc, 0, 110);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  
    lv_obj_align(arc, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_size(arc,size,size);
    lv_obj_set_style_arc_color(arc,lv_palette_main(LV_PALETTE_CYAN),LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc,lv_palette_darken(LV_PALETTE_GREY,3),LV_PART_MAIN);
    lv_anim_init(&arc_anim);
    lv_anim_set_var(&arc_anim, arc);
    lv_anim_set_exec_cb(&arc_anim, animation_callback);
    set_load(0);
}

void
LoadMeter::set_load(int val) {
    lv_anim_set_values(&arc_anim, load, val);
    load = val;
    lv_anim_start(&arc_anim);
}

void
LoadMeter::set_rotation(int val) {
    lv_arc_set_rotation(arc,val);
}

void
LoadMeter::set_angles(int a, int b) {
   lv_arc_set_bg_angles(arc, a, b);
}

void 
LoadMeter::set_reverse(bool rev) {
    lv_arc_set_mode(arc, rev ? LV_ARC_MODE_REVERSE : LV_ARC_MODE_NORMAL);
}

void
LoadMeter::set_visibility(bool visibility) {
    if (visibility) { 
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_HIDDEN);
    } else {
    lv_obj_add_flag(arc, LV_OBJ_FLAG_HIDDEN);
    }
}

LabelLine::LabelLine(lv_point_precise_t * points, int num) {
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_CYAN));
    lv_style_set_line_rounded(&style_line, true);
    line_l = lv_line_create(lv_screen_active());
    lv_line_set_points(line_l, points, num);
    lv_obj_add_style(line_l, &style_line, 0);
    lv_obj_center(line_l);
}

void
LabelLine::set_offsets(int x_offset, int y_offset) {
    lv_obj_align(line_l, LV_ALIGN_CENTER, x_offset, y_offset);
}

void
LabelLine::set_visibility(bool visibility) {
    if (visibility) { 
    lv_obj_remove_flag(line_l, LV_OBJ_FLAG_HIDDEN);
    } else {
    lv_obj_add_flag(line_l, LV_OBJ_FLAG_HIDDEN);
    }
}

Label::Label(int x_offset, int y_offset, const lv_font_t * font) {
    label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);    
    lv_label_set_text(label, "Label");
    lv_obj_set_width(label, LV_SIZE_CONTENT); 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_style_text_color(label,lv_palette_main(LV_PALETTE_CYAN),0); 
    lv_obj_set_style_text_font(label,font,0);
}

void
Label::set_text(const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    vsprintf(str, msg, ap);
    va_end(ap);
    lv_label_set_text(label, str);
}

void
Label::set_visibility(bool visibility) {
    if (visibility) { 
    lv_obj_remove_flag(label, LV_OBJ_FLAG_HIDDEN);
    } else {
    lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    }
}