Learn Allegro
================================

*Official _website_ [Allegro](http://alleg.sourceforge.net/).*

This is a port of source code of [2D Game Development Course](http://fixbyproximity.com/2d-game-development-course/) to pure C.


> "This course is a complete overview of 2D game development. 
It was made with beginning programmers in mind and focuses on fundamentals and low skill set solutions. 
The materials are written in C++ and utilize the Allegro 5 library. Enjoy!"


Below are the parts which the port was made.


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
-------------------------
* [Eclipse CDT](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/junor)
	- Escolher a versão compatível com o sistema operacional
	- Baixar e descompactar em alguma pasta. Eclipse pronto!

* [Java JDK](http://www.oracle.com/technetwork/java/javase/downloads/jdk-7u3-download-1501626.html)
	- Escolher a versão compatível com o sistema operacional
	- Instalar a JDK

* [MinGW](http://sourceforge.net/projects/mingw/files/Installer/mingw-get-inst/mingw-get-inst-20120426/)
	- Baixar o instalador mingw-get-inst-20120426.exe
	- next -> next -> escolher download latest repository catalogs e next -> next -> next -> escolher os compiladores C, C++ e MinGW Developer Toolkit e next -> Install

* [Cmake](http://cmake.org/cmake/resources/software.html)
	- Baixar o instalador Windows (Win32 Installer)
	- Instale o Cmake. Na guia "Install Options", escolha "add Cmake to the system path for all users"

* ?? [GTK](http://www.gtk.org/download/index.php)
	- Escolher a versão compatível com o sistema operacional
	
	
* [dx80_mgw.zip](http://www.liballeg.org/wip.html)
	- Encontre e baixo o arquivo dx80_mgw.zip
	- Descompacte na pasta C:\MinGW (ou onde vc instalou o MinGW)
	- Sobrescreva os arquivos que tem o mesmo nome

* [Allegro5](http://www.liballeg.org/wip.html)
	- Baixe a versão mais atual (5.0.7) da Allegro
	- Descompacte na pasta C:/Allegro5
	- Crie um diretorio "build" dentro desta pasta
	- Abra o prompt de comando (CMD) e vá para o diretorio C:/Allegro5/build
	- Digite os comandos:
		- cmake .. -G "MinGW Makefiles"
		- mingw32-make
		- mingw32-make install

Configurando o Eclipse
-------------------------
* Abra o Eclipse e crie um novo projeto C do tipo “Executable - Empty Project”
* Escolha "MinGW GCC" nas opções "Toolchains"
* Clique em Next -> Advanced settings...
* Selecione  “C/C++ Build”
* Selecione “Settings”
* Selecione “Configuration:” = “[All configurations]"
* Selecione  “MinGW C Linker”
* Selecione “Libraries”
* Na seção “Librairies (-l)” adicione "liballegro"
* Na seção  “Librairy search path (-L)” adicione “C:\MinGW\lib”
* Crie um novo arquivo de fonte C
* Insira o código abaixo:

<pre><code>
    #include <allegro.h>
    #include <stdlib.h>
 
    int main(void)
    {
        allegro_init();
        allegro_message("Hello World!");
        return EXIT_SUCCESS;
    }
</code></pre>

* "Build" o projeto
* Copie a C:\allegro5\build\lib\allegro.dll e coloque no diretório Debug
* Execute o projeto



Configurando as variáveis de ambiente
-------------------------
* No windows explorer clicar com o botão direito em "Computador" -> Propriedades
* Ir em Configurações Avançadas -> Variaveis de Ambiente
* Na segunda caixa, "Variaveis do sistema", encontrar a variavel "Path" -> selecione e escolha editar
* No final do Valor da variável incluir: ;C:\MinGW\bin (com o ";"!!!)




----------------------

> "SE EM TUDO O MAIS FOREM IDÊNTICAS AS VÁRIAS EXPLICAÇÕES DE UM FENÔMENO, A MAIS SIMPLES É A MELHOR" — WILLIAM DE OCKHAM

----------------------

Other helpful sources: [Allegro Community] [1],
[Allegro Wiki] [2] and [Deitel Allegro Resources] [3].

  [1]: http://www.allegro.cc/        "Allegro Community"
  [2]: http://wiki.allegro.cc/  "Allegro Wiki"
  [3]: http://www.deitel.com/ResourceCenters/Programming/C/AllegroCGameProgramming/tabid/223/Default.aspx    "Deitel Allegro Resources"