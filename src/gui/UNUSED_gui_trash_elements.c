

// nk_label_colored(g_nk_context, "Sphere", NK_TEXT_LEFT, nk_rgb(255, 255, 0));
/*
static int active = 0;
nk_layout_row_dynamic(g_nk_context, 30, 2);
        if (nk_option_label(g_nk_context, "easy", active == 0))
            active = 0;
        if (nk_option_label(g_nk_context, "hard", active == 1))
            active = 1;
*/

/*
void	display_loading()
{
// if (show_app_about && nk_begin(gui->g_nk_context, "Loading", nk_rect(500, 100, 0, 0),
	// 		NK_WINDOW_TITLE))
	// {
	// 	static struct nk_rect s = {0, 0, 300, 120};
	// 	if (nk_popup_begin(gui->g_nk_context, NK_POPUP_STATIC, "Loading", NK_WINDOW_TITLE|NK_WINDOW_BORDER, s))
	// 	{
	// 		nk_layout_row_dynamic(gui->g_nk_context, 25, 1);
	// 		if (prog_value < 50)
	// 			nk_label(gui->g_nk_context, "Step 1", NK_TEXT_LEFT);
	// 		else
	// 			nk_label(gui->g_nk_context, "Step 2", NK_TEXT_LEFT);
	// 			nk_progress(gui->g_nk_context, &prog_value, 100, NK_MODIFIABLE);
	// 			nk_popup_end(gui->g_nk_context);
	// 	}
	// }	
	// if (show_app_about)
	// 	nk_end(gui->g_nk_context);
}
*/

/*
	// if (image_active)
	// {
	// 	if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Image Popup", 0, nk_rect(190, 30, 320, 515)))
	// 	{
	// 		nk_layout_row_dynamic(g_nk_context, 80, 3);
	// 		while (i < 6)
	// 		{
	// 			if (nk_button_image(g_nk_context, gui_images[i]))
	// 			{
	// 				scene = i;
	// 				nk_popup_close(g_nk_context);
	// 			}
	// 			i++;
	// 		}
	// 	}
	// 	scenes_controls();
	// 	nk_popup_end(g_nk_context);
	// }
*/

/*
static void control_buttons(void)
{
	nk_button_set_behavior(g_nk_context, NK_BUTTON_REPEATER);
	nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_UP) ?
		fprintf(stdout, "Move UP!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);
	nk_button_symbol_label(g_nk_context, NK_SYMBOL_TRIANGLE_UP, "In",
		NK_TEXT_LEFT) ?	fprintf(stdout, "Move IN!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_LEFT) ?
		fprintf(stdout, "Move LEFT!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_DOWN) ?
		fprintf(stdout, "Move DOWN!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_RIGHT) ?
		fprintf(stdout, "Move RIGHT!\n") : 0;
	nk_button_symbol_label(g_nk_context, NK_SYMBOL_TRIANGLE_DOWN, "Out",
		NK_TEXT_LEFT) ?	fprintf(stdout, "Move OUT!\n") : 0;
	nk_button_set_behavior(g_nk_context, NK_BUTTON_DEFAULT);
}
*/
/*
void	display_mainmnu(void)
{
	if (nk_begin(g_nk_context, "Menu", nk_rect(10, 5, 220, 545),
			NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Scene", NK_MAXIMIZED)) //ON RELEASE: Minimized
		{
			display_scenes();
			// nk_label(g_nk_context, "Move your eye in scene", NK_TEXT_LEFT);
			// nk_layout_row_template_begin(g_nk_context, 0);
			// nk_layout_row_template_push_static(g_nk_context, 28);
			// nk_layout_row_template_push_static(g_nk_context, 28);
			// nk_layout_row_template_push_static(g_nk_context, 28);
			// nk_layout_row_template_push_static(g_nk_context, 75);
			// control_buttons();
			// nk_layout_row_template_end(g_nk_context);
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			if (nk_button_label(g_nk_context, "Take-a-Snapshot"))
				screen_shot();
			nk_tree_pop(g_nk_context);
		}
		shapes_tree();
	}
	nk_end(g_nk_context);
}

void	display_console(void)
{
	if (nk_begin(g_nk_context, "Information log", nk_rect(240, 650, 820, 245),
	NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// static char text[100];
		// static int text_len;
		// static char box_buffer[1024];
		static int box_len;
		// nk_flags active;
		// nk_layout_row_static(g_nk_context, 30, 790, 1);
		// active = nk_edit_string(g_nk_context, NK_EDIT_FIELD|NK_EDIT_SIG_ENTER,
		// 	text, &text_len, 100, nk_filter_ascii);
		// if (active & NK_EDIT_COMMITED)
		// {
		// 	text[text_len] = '\n';
		// 	text_len++;
		// 	memcpy(&box_buffer[box_len], &text, (nk_size)text_len);
		// 	box_len += text_len;
		// 	bzero(text, 100);
		// 	text_len = 0;
		// }
		box_len = ft_strlen(log_buf);
		
		nk_layout_row_static(g_nk_context, 190, 790, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX|NK_EDIT_SIG_ENTER, log_buf,
			&box_len, 4096, nk_filter_binary);
	}
	nk_end(g_nk_context);
}
*/

/*
void display_input_win(void)
{
	// if (nk_begin(g_nk_context, "Command line", nk_rect(CMD_X, CMD_Y, CMD_WIDTH, CMD_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	// {
	// 	static char text[100];
	// 	static int text_len;
	// 	static char box_buffer[10];
	// 	static int box_len;
	// 	nk_flags active;
	// 	nk_layout_row_static(g_nk_context, 30, 193, 1);
	// 	active = nk_edit_string(g_nk_context, NK_EDIT_FIELD | NK_EDIT_SIG_ENTER,
	// 							text, &text_len, 100, nk_filter_ascii);
	// 	if (active & NK_EDIT_COMMITED)
	// 	{
	// 		text[text_len] = '\n';
	// 		text_len++;
	// 		memcpy(&box_buffer[box_len], &text, (nk_size)text_len);
	// 		box_len += text_len;
	// 		bzero(text, 100);
	// 		text_len = 0;
	// 	}
	// 	nk_layout_row_static(g_nk_context, 250, 193, 1);
	// 	nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, box_buffer,
	// 				   &box_len, 512, nk_filter_binary);
	// }
	// nk_end(g_nk_context);
}
*/

// t_byte *pixels = malloc(sizeof(t_byte) * ((512 * 512) * 3));

// glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

// // glGetTextureImage()
// //TRY TO TARGA

// tga_image *dest = ft_memalloc(((512 * 512) * 3));
// tga_read(dest, "/Users/pzubar/RT/img/lights-03.tga");
// // tga_write_rgb(buffer, surf, (uint16_t)g_frame_width, (uint16_t)g_frame_height, 24);
// tga_write("/Users/pzubar/RT/img/NEW.bmp", dest);
// uint8_t *pixels = tga_find_pixel(dest, uint16_t x, uint16_t y);
// tga_write_rgb("/Users/pzubar/RT/img/NEW.bmp", pixels, (uint16_t)512, (uint16_t)512, 24);

// void	ui_delete_images(void)
// {
// 	glDeleteTextures(9, g_gl_image_textures);
// }


	/*
    // static int active1 = 0;
    static int active2 = 0;
    static int active3 = 0;
    // static int active4 = 0;
    struct nk_rect rect = nk_rect(10, 10, 600, 300);
    if (nk_begin(g_nk_context, "Bug Demo", rect, NK_WINDOW_MOVABLE | NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE))
    {
        int id = 0;
        struct nk_rect w;
        if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Children", NK_MAXIMIZED, id++))
        {
            if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Expand Me", NK_MINIMIZED, id++))
            {
                w = nk_layout_widget_bounds(g_nk_context);
                nk_layout_row_begin(g_nk_context, NK_STATIC, 18, 2);
                nk_layout_row_push(g_nk_context, 24);

                nk_button_label(g_nk_context, "...");
                nk_layout_row_push(g_nk_context, w.w - 24);

                nk_selectable_label(g_nk_context, "Hello", NK_TEXT_ALIGN_LEFT, &active2);
                nk_layout_row_end(g_nk_context);
                nk_tree_pop(g_nk_context);
            }
            w = nk_layout_widget_bounds(g_nk_context);
            nk_layout_row_begin(g_nk_context, NK_STATIC, 18, 2);
            nk_layout_row_push(g_nk_context, 24);

            nk_button_label(g_nk_context, "...");
            nk_layout_row_push(g_nk_context, w.w - 24);

            nk_selectable_label(g_nk_context, "I will disappear.", NK_TEXT_ALIGN_LEFT, &active3);
            nk_layout_row_end(g_nk_context);
            nk_tree_pop(g_nk_context);
        }
    }
    nk_end(g_nk_context);


                nk_layout_row_static(g_nk_context, 5, 30, 1);
                // nk_layout_row_dynamic(g_nk_context, 1, 1);
                struct nk_rect bounds = nk_widget_bounds(g_nk_context);

                if (nk_contextual_begin(g_nk_context, 0, nk_vec2(100, 300), bounds))
                {
                    nk_layout_row_dynamic(g_nk_context, 25, 1);
                    nk_label(g_nk_context, "Right click me for menu", NK_TEXT_LEFT);
                    // nk_checkbox_label(ctx, "Menu", &show_menu);
                    ft_printf("HELLO\n", shape->addr);
                    nk_contextual_end(g_nk_context);
                }


    */
   