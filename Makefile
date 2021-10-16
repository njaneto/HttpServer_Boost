.SUFFIXES:
.SUFFIXES: .o .ec .cpp

#pathprj=$(shell dirname $(shell dirname `pwd`))
pathprj=${PWD}
dirAplicacao=$(pathprj)/bin
dirBiblioteca=$(pathprj)/lib

binario=httpServer
nomeAplicacao=$(dirAplicacao)/$(binario)

versao=$(shell svnversion -n | grep '[0-9]' )

GCC_VERSION_C11 := $(shell expr `g++ -dumpversion | cut -f1-2  -d.` \>= 4.8 )

ifeq ($(GCC_VERSION_C11),1)
   CC = g++ -std=c++11 -Wall -Werror -rdynamic -DIFX_THREAD -D_REENTRANT -D_AUTORIZADOR_LINUX -DSVN_REVISION=\"$(versao)\"
else
	CC = g++ -std=c++98 ${GCC_VERSION} -Wall -Werror -rdynamic -DIFX_THREAD -D_REENTRANT -D_AUTORIZADOR_LINUX -DSVN_REVISION=\"$(versao)\"
endif

SO_KERNEL_NAME	= $(shell uname)
SO_PLATAFORM	= $(shell uname -i)

AR = ar
XSD = xsd

DIR_SRC= ./

DIR_CPP_ORIZON 	= $(BASE_ORIZON_PRJ)/include

#-----------------------------------------------------
#Diretorios dos arquivos header (.h) do ESPECIFICO
#-----------------------------------------------------
INCLUDE_DIR	  =  -I$(DIR_SRC)
ifneq ($(BASE_BOOST),)
	INCLUDE_DIR   += -I${BASE_BOOST}
endif


#-----------------------------------------------------
#Especifico
#-----------------------------------------------------
SRCS_CPP    = $(shell ls $(DIR_SRC)/src/*.cpp 2> /dev/null)
OBJS 		= $(SRCS_CPP:.cpp=.o)


#LIB_OMR = -L $(dirBiblioteca) -lOmrUtil -lOmrDataSource -lOmrPesquisas -lOmrGrafos

ifeq ($(SO_KERNEL_NAME),Linux)
	LIB_SYS 		= -lpthread -ldl -lcrypt -lc
else
	LIB_SYS			= <<especificar para o SO>>
endif
ifneq ($(BASE_BOOST_LIBS),)
	LIB_BOOST = -lcppunit -lodbc \
		-L ${BASE_BOOST_LIBS} -lboost_log -lboost_log_setup -lboost_filesystem -lboost_system -lboost_iostreams -lboost_date_time -lboost_regex -lboost_thread -lboost_chrono
endif
#Link das Bibliotecas
LINK		= $(LIB_SYS) $(LIB_BOOST)

.cpp.o:
	@echo "Compilando >>> $<"
	$(CC) -Wno-deprecated  $(INCLUDE_DIR) -c $< -o $@

all: $(OBJS)
	@echo "------------------------------------------------------------------------------"
	@[ -d $(dirAplicacao) ] || mkdir $(dirAplicacao)

	@echo "Criando autorizador <$(nomeAplicacao)>"
	@rm -f $(nomeAplicacao)
	$(CC)  $(LINK) -o $(nomeAplicacao) $?

	ln -sf $(dirAplicacao)/$(binario) $(binario) 
	@chmod 770 $(nomeAplicacao)
	@echo "<<<<<< Feito >>>>>>"
	@echo "------------------------------------------------------------------------------"

local: $(OBJS)
	@echo "----------------------------------------"
	@echo "Criando autorizador <$(nomeAplicacao)>"
	@rm -f $(nomeAplicacao)
	@$(CC) $?  $(LINK) -o $(nomeAplicacao)
	@chmod 770 $(nomeAplicacao)
	@echo "<<<<<< Feito >>>>>>"
	@echo "----------------------------------------"

clean:
	@echo "-------------------------------------------------"
	@echo "Apagando Objs/dependencias de <$(nomeAplicacao)>"
	rm -f $(OBJS:.o=.d) $(OBJS) core* $(nomeAplicacao)
	@echo "<<<<<< Feito >>>>>>"
	@echo "-------------------------------------------------"

-include $(OBJS:.o=.d)