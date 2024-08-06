#include "lvgl.h"
#include "display_interface.hpp"
#include <stdio.h>

/*char pct[4];
lv_obj_t * cpu_pct;
lv_obj_t * cpu_temp_label;
lv_obj_t * gpu_arc;
lv_anim_t gpu_arc_anim;
lv_obj_t * gpu_pct;
lv_obj_t * gpu_temp_label;
lv_obj_t * usb_connection_label;*/

void interface_init(){
    lv_obj_set_style_bg_color ( lv_screen_active() , lv_palette_darken(LV_PALETTE_GREY,4),0) ;
    lv_obj_set_scrollbar_mode(lv_screen_active(), LV_SCROLLBAR_MODE_OFF);
    
    /*Cpu percent
    cpu_pct = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(cpu_pct, LV_LABEL_LONG_WRAP);     
    lv_label_set_text(cpu_pct, "0%%");
    lv_obj_set_width(cpu_pct, 50);  
    lv_obj_set_style_text_align(cpu_pct, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(cpu_pct, LV_ALIGN_CENTER, -38, -61);
    lv_obj_set_style_text_color(cpu_pct,lv_palette_main(LV_PALETTE_CYAN),0);
    /*Gpu percent
   gpu_pct = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(gpu_pct, LV_LABEL_LONG_WRAP);     
    lv_label_set_text(gpu_pct, "0%%");
    lv_obj_set_width(gpu_pct, 50);  
    lv_obj_set_style_text_align(gpu_pct, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(gpu_pct, LV_ALIGN_CENTER, 38, -61);
    lv_obj_set_style_text_color(gpu_pct,lv_palette_main(LV_PALETTE_CYAN),0);  

      /*Cpu label
    lv_obj_t * name_l = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(name_l, LV_LABEL_LONG_WRAP);     //Break the long lines
    lv_label_set_text(name_l, "CPU");
    lv_obj_set_width(name_l, 50);  //Set smaller width to make the lines wrap
    lv_obj_set_style_text_align(name_l, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(name_l, LV_ALIGN_CENTER, -38, -43);
    lv_obj_set_style_text_color(name_l,lv_palette_main(LV_PALETTE_CYAN),0);
   
    /*Gpu label
    lv_obj_t * name_r = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(name_r, LV_LABEL_LONG_WRAP);    
    lv_label_set_text(name_r, "GPU");
    lv_obj_set_width(name_r, 50); 
    lv_obj_set_style_text_align(name_r, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(name_r, LV_ALIGN_CENTER, 38, -43);
    lv_obj_set_style_text_color(name_r,lv_palette_main(LV_PALETTE_CYAN),0);  

    /*Line points
    static lv_point_precise_t pct_line_l_points[] = { {42, 55}, {65, 68},{100, 68}};
    static lv_point_precise_t pct_line_r_points[] = { {198, 55}, {175, 68},{140, 68}};
    static lv_point_precise_t div_points[] = { {120, 40}, {120, 200}};

    /*line style
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_CYAN));
    lv_style_set_line_rounded(&style_line, true);

    /*Divider style
    static lv_style_t style_divider;
    lv_style_init(&style_divider);
    lv_style_set_line_width(&style_divider, 4);
    lv_style_set_line_color(&style_divider, lv_palette_darken(LV_PALETTE_GREY,3));
    lv_style_set_line_rounded(&style_divider, true);

    /*Divider
    lv_obj_t * div;
    div = lv_line_create(lv_screen_active());
    lv_line_set_points(div, div_points, 2);
    lv_obj_add_style(div, &style_divider, 0);
    lv_obj_center(div);
    lv_obj_set_width(div, 240);
    lv_obj_set_height(div, 240);

    /*Cpu load line
    lv_obj_t * pct_line_l;
    pct_line_l = lv_line_create(lv_screen_active());
    lv_line_set_points(pct_line_l, pct_line_l_points, 3);
    lv_obj_add_style(pct_line_l, &style_line, 0);
    lv_obj_center(pct_line_l);
    lv_obj_set_width(pct_line_l, 240);
    lv_obj_set_height(pct_line_l, 240);

    /*Gpu load line
    lv_obj_t * pct_line_r;
    pct_line_r = lv_line_create(lv_screen_active());
    lv_line_set_points(pct_line_r, pct_line_r_points, 3);
    lv_obj_add_style(pct_line_r, &style_line, 0);
    lv_obj_center(pct_line_r);
    lv_obj_set_width(pct_line_r, 240);
    lv_obj_set_height(pct_line_r, 240);
    
    /*Cpu temperature label
    cpu_temp_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(cpu_temp_label, LV_LABEL_LONG_WRAP);    
    lv_label_set_text(cpu_temp_label, "50°");
    lv_obj_set_width(cpu_temp_label, 70); 
    lv_obj_set_style_text_align(cpu_temp_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(cpu_temp_label, LV_ALIGN_CENTER, -60, 0);
    lv_obj_set_style_text_color(cpu_temp_label,lv_palette_main(LV_PALETTE_CYAN),0); 
    lv_obj_set_style_text_font(cpu_temp_label,&lv_font_montserrat_30,0);
    
    /*Gpu temperature label
    gpu_temp_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(gpu_temp_label, LV_LABEL_LONG_WRAP);    
    lv_label_set_text(gpu_temp_label, "50°");
    lv_obj_set_width(gpu_temp_label, 70); 
    lv_obj_set_style_text_align(gpu_temp_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(gpu_temp_label, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_style_text_color(gpu_temp_label,lv_palette_main(LV_PALETTE_CYAN),0); 
    lv_obj_set_style_text_font(gpu_temp_label,&lv_font_montserrat_30,0);

    /*Usb connection label
    usb_connection_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(usb_connection_label, LV_LABEL_LONG_WRAP); 
    lv_label_set_text(usb_connection_label, LV_SYMBOL_USB);
    lv_obj_set_width(usb_connection_label, 70); 
    lv_obj_set_style_text_align(usb_connection_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(usb_connection_label, LV_ALIGN_CENTER, 0, -100);
    lv_obj_set_style_text_color(usb_connection_label,lv_palette_main(LV_PALETTE_RED),0);*/ 
    //lv_obj_set_style_text_font(usb_connection_label,&lv_font_montserrat_30,0);

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

/*void set_cpu_temp(uint32_t temp){
    sprintf(pct,"%i°",(int)temp);
    lv_label_set_text(cpu_temp_label, pct);
}
void set_gpu_temp(uint32_t temp){
    sprintf(pct,"%i°",(int)temp);
    lv_label_set_text(gpu_temp_label, pct);
}
void set_cpu_load(uint32_t load, uint32_t load_old){
    lv_anim_set_values(&cpu_arc_anim, load_old, load);
    lv_anim_start(&cpu_arc_anim);
    sprintf(pct,"%i%%",(int)load);
    lv_label_set_text(cpu_pct, pct);
}
void set_gpu_load(uint32_t load, uint32_t load_old){
    lv_anim_set_values(&gpu_arc_anim, load_old, load);
    lv_anim_start(&gpu_arc_anim);
    sprintf(pct,"%i%%",(int)load);
    lv_label_set_text(gpu_pct, pct);
}
void set_usb_status(uint8_t status){
    switch (status){
    case USB_OK:
        lv_label_set_text(usb_connection_label, "");
        break;
    case USB_DISCONNECTED:
        lv_label_set_text(usb_connection_label, LV_SYMBOL_USB);
        set_cpu_temp(0);
        set_gpu_temp(0);
        set_cpu_load(0,0);
        set_gpu_load(0,0);
        break;
    default:
        lv_label_set_text(usb_connection_label, LV_SYMBOL_USB);
        set_cpu_temp(0);
        set_gpu_temp(0);
        set_cpu_load(0,0);
        set_gpu_load(0,0);
        break;
    }
}*/