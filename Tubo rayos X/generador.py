# -*- coding: utf-8 -*-
"""
Created on Fri Feb 23 15:04:04 2018

@author: hepf
"""

import numpy as np


Numero_total_particulas = 10000
Numero_particulas_corrida = 10000

salida = open("generado.mac",'w')

encabezado = "/control/verbose 0\n"
encabezado = encabezado + "/tracking/verbose 0\n"
encabezado = encabezado + "/gps/particle gamma\n"
encabezado = encabezado + "/gps/position -0.5495 0.265 0.499 m\n"
encabezado = encabezado + "/gps/ang/type iso\n/gps/ang/maxtheta 11.418 deg\n"
encabezado = encabezado + "/gps/ene/type Arb\n"
encabezado = encabezado + "/gps/hist/file EspectroEnergia60keV.dat\n"
encabezado = encabezado + "/gps/hist/inter Exp\n"

salida.write(encabezado)

corridas = (int)(Numero_total_particulas / Numero_particulas_corrida)

print (corridas)

for i in range(0,corridas):
    r1, r2 = np.round(10000*np.random.rand(2),0)

    parametros_corrida = "\n\n"
    parametros_corrida = parametros_corrida + "# corrida " + str(i) + "\n"
    #parametros_corrida = parametros_corrida + "/random/setSeeds " + str(int(r1)) + " " + str(int(r2)) + "\n"
    parametros_corrida = parametros_corrida + "/run/beamOn " + str(Numero_particulas_corrida) + "\n"

    salida.write(parametros_corrida)  



salida.close()
#/run/beamOn 10000000
