#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const int LARGURA_TELA = 880;
const int ALTURA_TELA = 640;

int main ()
{
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *imagem = NULL;

	if(!al_init())
	{
		fprintf(stderr, "Falha ao iniciar o allegro.\n");
		al_destroy_display(janela);
		return -1;
	}

	if(!al_init_image_addon())
	{
		fprintf(stderr, "Falha ao iniciar o allegro imagem.\n");
		al_destroy_display(janela);
		return -1;
	}

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if(!janela)
	{
		fprintf(stderr, "Falha ao iniciar a imagem.\n");
		return -1;
	}

	imagem = al_load_bitmap("imagem.jpg");
	if(!imagem)
	{
		fprintf(stderr, "Falha ao carregar imagem.\n");
		al_destroy_display(janela);
		return -1;
	}

	al_draw_bitmap(imagem, 0, 0, 0);
	al_flip_display();
	al_rest(10.0);

	al_destroy_bitmap(imagem);
	al_destroy_display(janela);
	return 0;
}