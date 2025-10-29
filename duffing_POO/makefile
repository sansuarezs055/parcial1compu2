# ============================================================================
# Proyecto: Oscilador de Duffing acoplado
# Autores: Eric Jesús Arciniegas Barreto, Santiago Suárez Sánchez
# Fecha: 2025-10-28
# Descripción: Compilación, limpieza y documentación del proyecto.
# ============================================================================

# --- Variables ---
CXX := g++
CXXFLAGS := -std=gnu++17 -Wall -Iinclude
SRC := src/main.cpp
OUT := duffing
DOC_DIR := documents
RESULTS := results
LATEX_FILE := $(DOC_DIR)/informe.tex
PDF_FILE := $(DOC_DIR)/informe.pdf

# --- Reglas principales ---

# Compilar el ejecutable principal
all: $(OUT)

$(OUT): $(SRC)
	@echo "Compilando el programa principal..."
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)
	@echo "✅ Compilación exitosa. Ejecuta ./$(OUT) para correr el programa."

# Ejecutar el programa (crea carpeta results si no existe)
run: $(OUT)
	@mkdir -p $(RESULTS)
	@./$(OUT)

# Generar el documento PDF de análisis físico
doc:
	@echo " Compilando documento LaTeX..."
	cd $(DOC_DIR) && pdflatex -interaction=nonstopmode $(notdir $(LATEX_FILE))
	@echo "Documento generado en $(PDF_FILE)"

# Limpiar archivos binarios y auxiliares
clean:
	@echo " Limpiando archivos temporales..."
	rm -f $(OUT)
	rm -f $(DOC_DIR)/*.aux $(DOC_DIR)/*.log $(DOC_DIR)/*.out $(DOC_DIR)/*.toc
	@echo "Limpieza completa."

# Limpiar todo (binarios + PDF)
cleanall: clean
	rm -f $(PDF_FILE)
	@echo "Proyecto completamente limpio."

# Mostrar ayuda
help:
	@echo "=== Comandos disponibles ==="
	@echo " make            -> Compila el ejecutable"
	@echo " make run        -> Ejecuta el programa"
	@echo " make doc        -
