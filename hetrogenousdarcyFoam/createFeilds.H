/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    darcyFoam

Description
Solves velocity and pressure equation in porous meduim using Darcy's law
\*---------------------------------------------------------------------------*/


/*------------------------------Read Variable Feilds-----------------------------*/
    Info<<"Reading Pressure Field"<<endl;
    
    volScalarField p
    {
    IOobject(
    "p",
    runTime.timeName(),
    mesh,
    IOobject::MUST_READ,
    IOobject::AUTO_WRITE 
    ),
    mesh
    };
    
   Info<<"Reading Velocity Field"<<endl;
    volVectorField U
    {
    IOobject(
    "U",
    runTime.timeName(),
    mesh,
    IOobject::NO_READ,
    IOobject::AUTO_WRITE 
    ),
    mesh,
    dimensionedVector("U",dimensionSet(0,1,-1,0,0,0,0),vector::zero)
    };
    

/*------------------------------Read Constant Feilds-----------------------------*/  
    Info<<"Reading Transport Properties"<<endl;
    Info<<"Reading  Permeabilty from SetFeilds"<<endl;
IOdictionary transportProperties
(
IOobject
(  
    "transportProperties",
     runTime.constant(),
     mesh,
     IOobject::MUST_READ_IF_MODIFIED,
     IOobject::NO_WRITE
)
      
);    

dimensionedScalar k
(
   transportProperties.lookup("k")

);

    Info<<"Reading Viscosity"<<endl;
    dimensionedScalar mu("mu",dimensionSet(1,-1,-1,0,0,0,0),1e-05);
// ************************************************************************* //
