from tkinter import *
import ctypes
from random import randint

class Tela():
    def __init__(self):
        self.janela = Tk()

        # usu e o texto do usúario
        self.usu = StringVar()

        # minorin e o texto do chatbot
        self.minorin = StringVar()
        self.minorin.set('Olá sou Minorin as suas ordens.')

        self.configuracao()
        self.widgets()
        self.posicao()
        self.janela.mainloop()

    def botao_config(self):
        # codigo da mensagem que vai aparece como resposta do bot
        self.cod = randint(0, 2)

        # função chatbot do codígo c++
        self.minorin_func = ctypes.CDLL('minorin.so')

        self.minorin_func._Z7chatboti.restype = None
        self.minorin_func._Z7chatboti.argtype = ctypes.c_int

        # pegando o texto do usúario e colocando no self.usu
        self.usu_txt = self.textbox.get()
        self.usu.set(self.usu_txt)
        self.usu_txt = self.usu_txt.lower()

        # escrevendo no arquivo dados.txt
        with open('dados.txt', 'w') as arquivo:
            arquivo.write(self.usu_txt)

        self.minorin_func._Z7chatboti(self.cod)

        with open('dados.txt', 'r') as arquivo:
            arquivo = arquivo.read()

        self.minorin.set(arquivo)

        with open('dados.txt', 'w') as arquivo:
            arquivo.write('')

    def configuracao(self):
        self.janela.geometry("456x500")
        self.janela.minsize(456, 500)
        self.janela.title('Atendete Minorin')

    def widgets(self):
        self.usu_lab = Label(self.janela, textvariable=self.usu, font='arial 24', background="#737373")

        self.minorin_lab = Label(self.janela, textvariable=self.minorin, font='arial 24')

        self.textbox = Entry(self.janela, font='arial 24')

        self.botao = Button(self.janela, text='Enviar', font='arial 24', command=self.botao_config)

    def posicao(self):
        self.usu_lab.place(x=0, y=0, relheight=0.095)

        self.minorin_lab.place(x=0, rely=0.1, relheight=0.095)

        self.textbox.place(rely=0.904, x=0, relheight=0.095, relwidth=0.7)

        self.botao.place(rely=0.904, relx=0.70, relheight=0.095, relwidth=0.3)

Tela()