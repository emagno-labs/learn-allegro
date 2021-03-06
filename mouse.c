/*
 * mouse.c
 *
 *  Created on: 11/08/2012
 *      Author: eryckson
 */

#include <allegro5/allegro.h>
#include <stdio.h>

// Atributos da tela
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

int main_0(void)
{
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0;
    // Flag que condicionar� nosso looping
    int sair = 0;

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }

    // Configura o t�tulo da janela
    al_set_window_title(janela, "Rotinas de Mouse - www.rafaeltoledo.net");

    // Torna apto o uso de mouse na aplica��o
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padr�o do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o ret�ngulo central da tela
    area_central = al_create_bitmap(LARGURA_TELA / 2, ALTURA_TELA / 2);
    if (!area_central)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o bot�o para fechar a aplica��o
    botao_sair = al_create_bitmap(100, 50);
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar bot�o de sa�da.\\n");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\\n");
        al_destroy_display(janela);
        return -1;
    }

    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    // Flag indicando se o mouse est� sobre o ret�ngulo central
    int na_area_central = 0;
    while (!sair)
    {
        // Verificamos se h� eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            // Se o evento foi de movimenta��o do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                // Verificamos se ele est� sobre a regi�o do ret�ngulo central
                if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(area_central) / 2 &&
                    evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(area_central) / 2 &&
                    evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(area_central) / 2 &&
                    evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(area_central) / 2)
                {
                    na_area_central = 1;
                }
                else
                {
                    na_area_central = 0;
                }
            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10)
                {
                    sair = 1;
                }
            }
        }

        // Limpamos a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Colorimos o bitmap correspondente ao ret�ngulo central,
        // com a cor condicionada ao conte�do da flag na_area_central
        al_set_target_bitmap(area_central);
        if (!na_area_central)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }

        // Colorimos o bitmap do bot�o de sair
        al_set_target_bitmap(botao_sair);
        al_clear_to_color(al_map_rgb(255, 0, 0));

        // Desenhamos os ret�ngulos na tela
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(area_central, LARGURA_TELA / 2 - al_get_bitmap_width(area_central) / 2,
                       ALTURA_TELA / 2 - al_get_bitmap_height(area_central) / 2, 0);
        al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10,
                       ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10, 0);

        // Atualiza a tela
        al_flip_display();
    }

    // Desaloca os recursos utilizados na aplica��o
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(area_central);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
