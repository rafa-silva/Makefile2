#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
 
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;
 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *imagem_fundo = NULL;
ALLEGRO_FONT *fonte = NULL;
 
bool inicializar();
 
int main(void)
{
    bool sair = false;
    int tecla = 0;
 
    if (!inicializar())
    {
        return -1;
    }
    
    //A imagem de fundo da tela incial do jogo
    al_draw_bitmap(imagem_fundo, 0, 0, 0);

    //Escrita na tela sair e iniciar jogo da tela inicial
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Iniciar Jogo");

    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 400, ALLEGRO_ALIGN_CENTRE, "Sair");

    //looping do funcionamento das setas do teclado

    while (!sair)
    {
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    tecla = 1;
                    break;
                case ALLEGRO_KEY_DOWN:
                    tecla = 2;
                    break;
                case ALLEGRO_KEY_LEFT:
                    tecla = 3;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    tecla = 4;
                    break;
                    case ALLEGRO_KEY_ENTER:
                    tecla = 5;
                    break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
        }
        
        //Casos que ocorrem com cada seta da tecla na tela inicial
        if (tecla)
        {
            al_draw_bitmap(imagem_fundo, 0, 0, 0);

            al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Iniciar Jogo");
            al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 400, ALLEGRO_ALIGN_CENTRE, "Sair");
 
            switch (tecla)
            {
            //O jogo vai ser iniciado
            case 1:
                al_draw_textf(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Iniciar Jogo");
                break;

            //O jogo fecha se o usuario escolher e aperta enter, sair do jogo
            case 2:
                al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 400, ALLEGRO_ALIGN_CENTRE, "Sair");     
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            }
            if(tecla == 5){
                al_destroy_display(janela);
            }
            tecla = 0;
        }
 
        al_flip_display();
    }
 
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}
 
bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }
 
    al_init_font_addon();
 
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }
 
    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }
 
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }
 
    //Criando janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    
    //Nome da janela
    al_set_window_title(janela, "Se Aveturando no Trânsito");
 
    //O que representara o font
    fonte = al_load_font("keybp.ttf", 72, 0);
    if (!fonte)
    {
        fprintf(stderr, "Falha ao carregar \"fonte comic.ttf\".\n");
        al_destroy_display(janela);
        return false;
    }
 
    //Criando fila de eventos
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
 
    //Carregando imagem
    imagem_fundo = al_load_bitmap("pum.png");
    if (!imagem_fundo)
    {
        fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }
 
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
 
    return true;
}