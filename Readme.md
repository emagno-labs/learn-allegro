﻿Aprenda Allegro em C
================================

*_website_ Oficial [Allegro](http://alleg.sourceforge.net/).*

Os fontes deste projetos é um _port_ do código fonte do curso [2D Game Development Course](http://fixbyproximity.com/2d-game-development-course/), original em C++ para C.

Abaixo estão listados os capítulos do curso que o código foi migrado.

Part 5
-------------------------

* 5.0 – Our First Game
* 5.1 – Our First Game: The Player
* 5.2 – Our First Game: Timing and Movement
* 5.3 – Our First Game: The Projectiles
* 5.4 – Our First Game: The Enemies
* 5.5 – Our First Game: Collision Detection
* 5.6 – Our First Game: Game Logic
* 5.7 – Our First Game: Conclusion


Ambiente de desenvolvimento
================================

Precisamos montar um ambiente de desenvolvimento que nos possibilite trabalhar com a Allegro em C.
Abaixo vamos tratar de itens como compiladores, bibliotecas externas (dependências), IDE de desenvolvimento.
Na maioria dos casos os fontes das bibliotecas serão baixados e compilados utilizando o compilador que estaremos trabalhando.

Este tutorial descreve a configuração do ambiente de desenvolvimento em _Windows_, utilizando a IDE _Eclipse CDT_ e o _MinGW_ com seu **_port_** do GCC para Windows.

**Nos passos abaixo são sugeridos alguns diretórios padronizados, como _c:\Allegro5_, _c:\MinGW_ ou _c:\temp_**

Caso queira utilizar outros diretorios duas dicas:

* Não utilize _espaços_ no nome dos diretórios: _"Meus Documentos"_ ou _"Trabalho Facul"_ são exemplos que darão erro.
* Não se esqueça de substituir os caminhos mostrados no tutorial pelos caminhos que você escolheu. Óbvio. ¬¬


Compilador e _build system_
-----------------------------
* [MinGW](http://sourceforge.net/projects/mingw/files/Installer/mingw-get-inst/mingw-get-inst-20120426/)
	- Baixar o instalador mingw-get-inst-20120426.exe
	- next -> next -> escolher download latest repository catalogs e next -> next -> next -> escolher os compiladores C, C++ e MinGW Developer Toolkit e next -> Install

	- Pequena correção de um cabeçalho (.h) do MinGW:
		- Abra o "limits.h" que está em "C:/mingw/include" e inclua:
			- #define SIZE_T_MAX UINT_MAX /* max value for a size_t */
		- antes de (é a última linha do arquivo)
			- #endif /* not _LIMITS_H_ */

* [Cmake](http://cmake.org/cmake/resources/software.html)
	- Baixar o instalador Windows (Win32 Installer)
	- Instale o Cmake. Na guia "Install Options", escolha "add Cmake to the system path for all users"


Configurando as variáveis de ambiente
-------------------------
* No windows explorer clicar com o botão direito em "Computador" -> Propriedades
* Ir em Configurações Avançadas -> Variaveis de Ambiente
* Na segunda caixa, "Variaveis do sistema", encontrar a variavel "Path" -> selecione e escolha editar
	* No final do Valor da variável incluir: ;C:\MinGW\bin (com o ";"!!!)
* Criar variavel de ambiente MINGDIR
	* Configure o valor da MINGDIR para C:\MinGW\

Allegro 5
---------------------------
* [Allegro5](http://alleg.sourceforge.net/download.html) *Código Fonte*
	- Baixe a versão mais atual (allegro-5.0.7.zip) da Allegro
	- Descompacte na pasta C:/Allegro5
	- Crie um diretorio "build" dentro desta pasta (C:/Allegro5/build)
	- Crie um diretorio "deps" dentro desta pasta (C:/Allegro5/deps)

Dependências da Allegro
---------------------------
**Abaixo cada dependência tem um link para seu site oficial. Para facilitar, coloquei no [dropbox](https://www.dropbox.com/sh/co2bzmkbjuma2sh/oHcW18R44D/pi/allegro5-deps) estes pacotes.**

* [Ogg (libogg)](http://xiph.org/downloads/) *Código Fonte*
	- descompacte para a pasta c:/temp/libogg
	- C:\MinGW\msys\1.0\msys.bat
		- cd c:/temp/libogg
		- ./configure
		- make
		- make install
	- crie o diretorio "libogg" em C:/Allegro5/deps
	- copie de C:\MinGW\msys\1.0\local as pastas para a pasta C:/Allegro5/deps/libogg
	- copie de C:\MinGW\msys\1.0\local para C:\MinGW
	- apague o conteudo de C:\MinGW\msys\1.0\local

* [Vorbis(libvorbis)](http://xiph.org/downloads/) *Código Fonte*
	- descompacte para a pasta c:/temp/libvorbs
	- C:\MinGW\msys\1.0\msys.bat
		- cd c:/temp/libvorbs
		- ./configure
		- make
		- make install
	- crie o diretorio "libvorbis" em C:/Allegro5/deps	
	- copie de C:\MinGW\msys\1.0\local as pastas para a pasta C:/Allegro5/deps/libvorbis
	- apague o conteudo de C:\MinGW\msys\1.0\local

* [FLAC](http://sourceforge.net/projects/flac/files/flac-src/flac-1.2.1-src/) *Código Fonte*
	- descompacte para a pasta c:/temp/flac
	- C:\MinGW\msys\1.0\msys.bat
		- cd c:/temp/flac
		- ./configure
		- make
			- _Alguns erros podem ser exibidos no final do processo, se forem relacionados a pasta **examples** são erros esperados. Não se preocupe, a biblioteca terá sido compilada com sucesso._
		- make install
	- crie o diretorio "flac" em C:/Allegro5/deps
	- copie de C:\MinGW\msys\1.0\local as pastas para a pasta C:/Allegro5/deps/flac
	- apague o conteudo de C:\MinGW\msys\1.0\local

* [DUMB](http://dumb.sourceforge.net/index.php?page=downloads) *Código Fonte*
	- descompacte para a pasta c:/temp/dumb
	- vá para o prompt de comando (iniciar -> executar -> cmd) 
	- cd c:/temp/dumb
	- mingw32-make
		- Would you like to compile DUMB for DJGPP or MinGW (D/M)? M
		- Would you like support for Allegro (Y/N) N
	- crie o diretorio "dumbs" em C:/Allegro5/deps
	- copie de c:/temp/dumb as pastas "lib" e "include" para a pasta C:/Allegro5/deps/dumbs

* [OpenAL](http://kcat.strangesoft.net/openal.html) *Binários*
	- baixe os binários para Windows
	- descompacte para a pasta c:/temp/openal
	- crie o diretorio "openal" em C:/Allegro5/deps
	- copie de c:/temp/openal as pastas "lib" e "include" para a pasta C:/Allegro5/deps/openal

* [FreeType](http://gnuwin32.sourceforge.net/packages/freetype.htm) *Binários*
	- baixe os binários para Windows
	- descompacte para a pasta c:/temp/freetype
	- crie o diretorio "freetype" em C:/Allegro5/deps
	- copie de c:/temp/freetype as pastas "lib" e "include" para a pasta C:/Allegro5/deps/freetype

* [dx9mgw.zip](http://alleg.sourceforge.net/download.html) *Binários*
	- Encontre e baixo o arquivo dx9mgw.zip
	- descompacte para a pasta c:/temp/dx9
	- copie de c:/temp/dx9 todas as pastas para a pasta C:\MinGW
		- Sobrescreva os arquivos que tem o mesmo nome


Compilando a Allegro 5
---------------------------
* Abra o prompt de comando (CMD) e vá para o diretorio C:/Allegro5/build
* Digite os comandos:
	- cmake .. -G "MinGW Makefiles"
		- **Cuidado!** É _case sensitive_
	- mingw32-make
	- mingw32-make install


Instalando a IDE Eclipse CDT
-------------------------
* [Java JDK](http://www.oracle.com/technetwork/java/javase/downloads/jdk-7u3-download-1501626.html)
	- Escolher a versão compatível com o sistema operacional
	- Instalar a JDK

* [Eclipse CDT](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/junor)
	- Escolher a versão compatível com o sistema operacional
	- Baixar e descompactar em alguma pasta. Eclipse pronto!


Configurando a IDE Eclipse CDT
-------------------------

* Abra o Eclipse e crie um novo projeto C 
* Dê um nome para seu projeto, por exemplo **TesteAllegro**
* Em **Project Type** escolha _Executable -> Empty Project_
* Em **Toolchains** escolha _MinGW GCC_
* Clique em Next -> Advanced settings...
* Selecione  _C/C++ Build -> Settings_
* Selecione “Configuration:” = “[All configurations]"
* Selecione  _MinGW C Linker -> Libraries_
* Na seção **Librairies (-l)** adicione *liballegro* e *liballegro_dialog*
* Na seção **Librairy search path (-L)** adicione _C:\MinGW\lib_
* Clique em Ok -> Finish
* Crie um novo _Source File_ 
* Dê um nome para seu código fonte, por exemplo **primeiroTeste.c** -> Finish
* Insira o código abaixo:

<pre><code>

#include &lt;allegro5/allegro.h&gt;
#include &lt;allegro5/allegro_native_dialog.h&gt;

int main(void) {
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
				"failed to initialize allegro!", NULL, NULL );
		return -1;
	}

	display = al_create_display(640, 480);

	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL,
				"failed to initialize display!", NULL, NULL );
		return -1;
	}

	al_show_native_message_box(display, "Algum Titulo", "Resultado da configuracao:",
					"Tudo okay!", NULL, NULL );

	al_destroy_display(display);

	return 0;
}
</code></pre>

* _Build_ o projeto (_Ctrl+B_ ou no menu _Project -> Build Project_). **Não execute o projeto ainda.**
* Copie a _C:\allegro5\build\lib\allegro-5.0.dll_ e coloque no diretório **Debug** do seu projeto (este diretório é criado quando fazemos o _Build_ do projeto)
* Refaça o _Build_ do projeto. **Agora não devem ser apresentados erros no código!**
* Execute o projeto =]


----------------------

> "SE EM TUDO O MAIS FOREM IDÊNTICAS AS VÁRIAS EXPLICAÇÕES DE UM FENÔMENO, A MAIS SIMPLES É A MELHOR" — WILLIAM DE OCKHAM

----------------------


Material de apoio para este _walkthrough_
-------------------------
* [Building Allegro 5.1 (rev 15032) Windows 7] [4]

* [Setting up Allegro to work with Eclipse on Windows XP] [5]

* Allegro 5 _Readme.txt_ (arquivo texto que vem junto com os códigos fontes e se encontra na raiz do diretório da Allegro)


Outros links úteis: [Allegro Community] [1],
[Allegro Wiki] [2] e [Deitel Allegro Resources] [3].

  [1]: http://www.allegro.cc/ "Allegro Community"
  [2]: http://wiki.allegro.cc/ "Allegro Wiki"
  [3]: http://www.deitel.com/ResourceCenters/Programming/C/AllegroCGameProgramming/tabid/223/Default.aspx "Deitel Allegro Resources"
  [4]: http://wiki.allegro.cc/index.php?title=Building_Allegro_5.1_(rev_15032)_Windows_7 "Building Allegro 5.1"
  [5]: http://wiki.allegro.cc/index.php?title=Eclipse#Setting_up_Allegro_to_work_with_Eclipse_on_Windows_XP "Setting up Allegro to work with Eclipse on Windows XP"