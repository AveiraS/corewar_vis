/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:04 by asmall            #+#    #+#             */
/*   Updated: 2020/06/17 22:32:35 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int			init_help(t_vm *vm)
{
	if (g_main_render == NULL)
	{
		ft_printf("Renderer could not be created! SDL Error: %s\n",
			SDL_GetError());
		return (0);
	}
	if (TTF_Init() < 0)
	{
		ft_printf("SDL_ttf couldn't initialize. SDL error: %s\n",
			TTF_GetError());
		return (0);
	}
	if (vm->num_players > 1)
		g_font = TTF_OpenFont("resource/InputMono-Regular.ttf",
			15 - (vm->num_players - 1));
	else
		g_font = TTF_OpenFont("resource/InputMono-Regular.ttf", 15);
	if (!g_font)
	{
		ft_printf("%s\n", TTF_GetError());
		return (0);
	}
	return (1);
}

int			init(t_vm *vm)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("SDL could not initialize. SDL error: %s\n",
			SDL_GetError());
		return (0);
	}
	g_main_window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
						SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
	{
		ft_printf("SDL could not create window. SDL error: %s\n",
			SDL_GetError());
		return (0);
	}
	g_main_render = SDL_CreateRenderer(g_main_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	init_help(vm);
	return (1);
}

void		set_render_draw_color(char color)
{
	if (color == 'r')
		SDL_SetRenderDrawColor(g_main_render, 155, 0, 0, 255);
	else if (color == 'y')
		SDL_SetRenderDrawColor(g_main_render, 155, 155, 0, 255);
	else if (color == 'g')
		SDL_SetRenderDrawColor(g_main_render, 0, 155, 0, 255);
	else if (color == 'b')
		SDL_SetRenderDrawColor(g_main_render, 0, 0, 155, 255);
	else if (color == 'p')
		SDL_SetRenderDrawColor(g_main_render, 155, 0, 155, 255);
	else if (color == 'c')
		SDL_SetRenderDrawColor(g_main_render, 0, 155, 155, 255);
	else if (color == 'e')
		SDL_SetRenderDrawColor(g_main_render, 155, 155, 155, 255);
	else if (color == 'l')
		SDL_SetRenderDrawColor(g_main_render, 50, 50, 50, 255);
	else
		SDL_SetRenderDrawColor(g_main_render, 111, 111, 111, 255);
}

void		visualizer_event(t_vm *vm)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
			&& event.key.keysym.sym == SDLK_ESCAPE))
			vm->vis_quit = 1;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			if (vm->vis_pause == 1)
				vm->vis_pause = 0;
			else
				vm->vis_pause = 1;
		}
	}
}
