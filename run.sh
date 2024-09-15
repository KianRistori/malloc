#!/bin/sh
# Aggiungi la directory corrente alla variabile LD_LIBRARY_PATH
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."

# Precarica la libreria personalizzata libft_malloc.so
export LD_PRELOAD="./libft_malloc.so"

# Esegui il programma passato come argomento allo script
exec "$@"

