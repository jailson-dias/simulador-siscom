#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /* Fini = 64
     * 
     */
    int fcur = 64, fini = 64, fsub = 0, ns = 0, nc = 0;
    int quanttags = 100;
    int quantslots = 64;
    
    while (quanttags > 0) {
        int slots[quantslots],
            sucesso = 0, // quantidade de slots que leram as etiquetas com sucesso
            colisao = 0, // quantidade de slots que tiveram colisao
            vazio = 0; // quantidade de slots vazios

        for (int i = 0; i< quantslots;i++) {
            slots[i] = 0; // coloca 0 em todos os slots
        }

        for (int i = 0; i < quanttags; i++) {
            slots[rand() % quantslots] += 1; // gera um numero aleatorio entre 0 e a quantidade de slots e no slot do numero que foi gerado acrescenta um nele
        }
        
        for (int i = 0; i< quantslots;i++) {
            if (slots[i] == 0) {
                vazio++; // pega a quantidade de slots vazios
            } else if (slots[i] == 1) {
                sucesso++; // pega a quantidade de slots que conseguiram reconhecer tags
            } else {
                colisao++; // pega a quantidade de slots que teve colisao
            }
        }
    }
	return 0;
}

/*
 * 1. Initialize F cur = F ini , F sub , N s and N c , where F ini and F sub are initial full frame and sub-frame size, respectively
 * 2. while (quanttags > 0)
 * 3. for (int i = 0; i < quanttags; i++) {
        slots[rand() % quantslots] += 1; // gera um numero aleatorio entre 0 e a quantidade de slots e no slot do numero que foi gerado acrescenta um nele
    }
 * 4. calcular sucesso e coliso
 * 5. Find n̂ from MAP tables and compute N est according to Eq.9
6. if F cur fits N est according to Table.I
7. Compute N back from Eq.11&12, and adjust next frame size
8 .Set K = 1 for the rest of the time
9. else
10. Compute N back from Eq.10 and adjust next frame size
11. end if
12. end while
 * 
 * 
 * incremento tags = 20
 * inicial tags = 6
*/


/*
 * F = Tamanho do frame, ex: 64 slots
 * ñ = Número estimado de tags no primeiro sub-frame
 * Fsub = Tamanho do sub-frame
 * Nest = Numero estimado de tags em todo o frame = ñ*K -> K = F/Fsub = quantidade de subframes
 * 
*/