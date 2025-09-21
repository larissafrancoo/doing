#ifndef CUB3D_H
# define CUB3D_H
# include "./mlx/mlx.h"
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIN_W 800
# define WIN_H 600
# define MOVE_SPEED 0.12
# define ROT_SPEED  0.06

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define MAX_TEX 4

# define EXIT_F 1
# define EXIT_S 0

typedef struct s_raio
{
	double	cam_x;
	double	r_dir_x;
	double	r_dir_y;
	int		map_x;
	int		map_y;
	double	delt_dis_x;
	double	delt_dis_y;
	double	sid_dis_x;
	double	sid_dis_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	per_wll_dis;
	int		line_h;
	int		drw_start;
	int		drw_end;
	int		tex_nu;
	int		tx_x;
	int		tx_y;
	double	tx_pos;
	double	step;
}	t_raio;

typedef struct s_infos
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_infos;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textura
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textura;

typedef struct s_config
{
	t_color			chao;
	t_color			teto;
	t_textura		tex;
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	px;
	double	py;
	char	direction;
}	t_player;

typedef struct s_map
{
	char	**grade;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_infos		img;
	t_infos		tex[MAX_TEX];
	t_config	config;
	t_map		map;
	t_player	player;
}	t_game;

int		open_cub(t_game *g, const char *path);
char	**read_all_lines(int fd, int *count);
int		find_map_start(char **lines, int lcount);
int		parse_config(char **lines, int start_map, t_config *config);
int		parse_line(char *line, t_config *config);
int		parse_map(char **lines, int start, t_map *map, t_player *player);
int		validar_mapa(t_map *map, t_player *player);
int		check_integridade(t_game *g);
int		load_tex(t_game *g, t_infos *tex, char *path);
int		load_all_texs(t_game *g);
int		setup_game(t_game *g, const char *path);
int		handle_key(int keycode, t_game *g);
int		can_move_to(t_game *g, double nx, double ny);
void	rotate_player(t_player *p, double angle);
int		is_valid_char(char c);
char	*lines_strdup(const char *s);
int		is_config_line(char *line);
int		validate_after_map(char **lines, int start_map, int lcount);
int		press_key(int keycode, t_game *game);
int		render_frame(t_game *g);
int		error_exit(t_game *g, const char *msg, int code);
void	free_map(t_map *m);
void	free_config(t_config *c);
void	free_player(t_player *p);
void	free_all(t_game *g);
void	destroi_texs(t_game *g);
int		close_game(t_game *g);
int		game_over(t_game *g);
int		error_msg(const char *msg, int code);
void	free_split(char **s);
void	my_mlx_pixel_put(t_infos *dado, int x, int y, int color);
void	desenha_linha_vert(t_game *g, int x, int start, int end, int cor);
int		rgb_to_int(t_color c);
int		prepara_frame(t_game *g);
void	limpa_bkg(t_game *g);
void	calc_direction(t_game *g, int x, t_raio *r);
void	calc_delta(t_raio *r);
void	calc_passos(t_game *g, t_raio *r);
void	inicializar_raio(t_game *g, int x, t_raio *r);
void	dar_passo(t_raio *r);
void	exec_dda(t_game *g, t_raio *r);
void	calc_linha(t_raio *r);
void	escolher_tex(t_raio *r);
double	calc_wall_x(t_game *g, t_raio *r);
void	calc_tex(t_game *g, t_raio *r, double wX);
void	draw_wall(t_game *g, int x, t_raio *r);
int		render_frame(t_game *g);

#endif
