
[Mesh]
    [gmshTest]
        type = gmshFile
        file = DivertorSimple.msh
        geofile = DivertorSimple.geo
        dim = 2
        param_names = 'Cooling_Tube_Thickness Intermediate_Thickness holeSize Thermal_Slit_Width'
        param_values = '0.002 0.001 0.005 0.0002'
    []
   
[]

[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Variables]
  [temp]
    initial_condition = 296 
  []
[]

[AuxVariables]
  [./eigenstrain_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./eigenstrain_xx]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./total_strain_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./total_strain_xx]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_xx_nodal]
    order = FIRST
    family = MONOMIAL
  [../]
  [./strain_xx_nodal]
    order = FIRST
    family = MONOMIAL
  [../]
  [./strain_yy_nodal]
    order = FIRST
    family = MONOMIAL
  [../]
  [./strain_zz_nodal]
    order = FIRST
    family = MONOMIAL
  [../]
  [./vonmises_nodal]
    order = FIRST
    family = MONOMIAL
  [../]
[]



[Kernels]
  [heat_conduction]
    type = ADHeatConduction
    variable = temp
  []
  [heat_conduction_time_derivative]
    type = ADHeatConductionTimeDerivative
    variable = temp
  []
  [body_force]
    type = ADBodyForce
    variable = temp
    value = 2e1 #W/m^2
  []
[]

[AuxKernels]
  [./eigenstrain_yy]
    type = ADRankTwoAux
    rank_two_tensor = eigenstrain
    variable = eigenstrain_yy
    index_i = 1
    index_j = 1
    execute_on = 'initial timestep_end'
  [../]
  [./eigenstrain_xx]
    type = ADRankTwoAux
    rank_two_tensor = eigenstrain
    variable = eigenstrain_xx
    index_i = 0
    index_j = 0
    execute_on = 'initial timestep_end'
  [../]

  [./total_strain_yy]
    type = ADRankTwoAux
    rank_two_tensor = total_strain
    variable = total_strain_yy
    index_i = 1
    index_j = 1
    execute_on = 'initial timestep_end'
  [../]
  [./total_strain_xx]
    type = ADRankTwoAux
    rank_two_tensor = total_strain
    variable = total_strain_xx
    index_i = 0
    index_j = 0
    execute_on = 'initial timestep_end'
  [../]
  [./stress_xx]
    type = ADRankTwoAux
    rank_two_tensor = stress
    variable = stress_xx_nodal
    index_i = 0
    index_j = 0
 [../]
 [./strain_xx]
    type = ADRankTwoAux
    rank_two_tensor = total_strain
    variable = strain_xx_nodal
    index_i = 0
    index_j = 0
 [../]
 [./strain_yy]
    type = ADRankTwoAux
    rank_two_tensor = total_strain
    variable = strain_xx_nodal
    index_i = 1
    index_j = 1
  [../]
 [./strain_zz]
    type = ADRankTwoAux
    rank_two_tensor = total_strain
    variable = strain_zz_nodal
    index_i = 2
    index_j = 2
  [../]
  [./vonmises]
    type = ADRankTwoScalarAux
    rank_two_tensor = stress
    variable = vonmises_nodal
    scalar_type = VonMisesStress
  [../]
[]

[Modules]
  [./TensorMechanics]
    [./Master]
      [./all]
        strain = FINITE
        incremental = true
        add_variables = true
        eigenstrain_names = eigenstrain
        use_automatic_differentiation = true
        generate_output = 'strain_xx strain_yy strain_zz vonmises_stress'
      [../]
    [../]
  [../]
[]


[Materials]
  [Tungsten_Thermal]
    type = ADHeatConductionMaterial
    specific_heat = 133.9776 # J/kg-K
    thermal_conductivity = 173 # W/m*K
    block = Tungsten
  []
  [Tungsten_density]
    type = ADGenericConstantMaterial
    prop_names = 'density'
    prop_values = '19600' #kg/m^3 @ 296K
    block = Tungsten
  []
  [Cu_thermal]
    type = ADHeatConductionMaterial
    specific_heat = 385 # J/kg-K
    thermal_conductivity = 	385 # W/m*K
    block = Intermediate
  []
  [Cu_density]
    type = ADGenericConstantMaterial
    prop_names = 'density'
    prop_values = '8960' #kg/m^3 @ 296K
    block = Intermediate
  []
  [CuCrZr_Thermal]
    type = ADHeatConductionMaterial
    specific_heat = 380 # J/kg-K
    thermal_conductivity = 335 # W/m*K
    block = CoolingTube
  []
  [CuCrZr_density]
    type = ADGenericConstantMaterial
    prop_names = 'density'
    prop_values = '8900' #kg/m^3 @ 296K
    block = CoolingTube
  []
  [./elasticity_tensor_tungsten]
    type = ADComputeIsotropicElasticityTensor
    youngs_modulus = 390E9
    poissons_ratio = 0.27
    block = Tungsten
  [../]
  [./thermal_expansion_strain_tungsten]
    type = ADComputeThermalExpansionEigenstrain
    stress_free_temperature = 1300
    thermal_expansion_coeff = 4.3E-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = Tungsten
  [../]
  [./elasticity_tensor_CoolingTube]
    type = ADComputeIsotropicElasticityTensor
    youngs_modulus = 121E9
    poissons_ratio = 0.34
    block = CoolingTube
  [../]
  [./thermal_expansion_strain_CoolingTube]
    type = ADComputeThermalExpansionEigenstrain
    stress_free_temperature = 450
    thermal_expansion_coeff = 16.7E-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = CoolingTube
  [../]
  [./elasticity_tensor_Itermediate]
    type = ADComputeIsotropicElasticityTensor
    youngs_modulus = 137E9
    poissons_ratio = 0.3
    block = Intermediate
  [../]
  [./thermal_expansion_strain_Itermediate]
    type = ADComputeThermalExpansionEigenstrain
    stress_free_temperature = 450
    thermal_expansion_coeff = 17E-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = Intermediate
  [../]
  [./finite_stress]
    type = ADComputeFiniteStrainElasticStress
  [../]
[]

[BCs]
  [Heat_In]
    type = ADNeumannBC
    variable = temp
    boundary = Top
    value =  5e6 # 5 MW/m^2
  []
  [Heat_Out]
    type = ADConvectiveHeatFluxBC
    variable = temp
    boundary = Tube_Hole_Boundary
    T_infinity = 300 #K
    heat_transfer_coefficient = 10
  []
  [bottom_Disp_x]
    type = ADDirichletBC
    variable = disp_x
    boundary = Bottom
    value = 0
  []
  [bottom_Disp_y]
    type = ADDirichletBC
    variable = disp_y
    boundary = Bottom
    value = 0
  []
[]



[Postprocessors]
  [avg]
    type = AverageNodalVariableValue
    variable = temp
  []
  [max]
    type = NodalExtremeValue
    variable = temp
    value_type = max
  []
  [min]
    type = NodalExtremeValue
    variable = temp
    value_type = min
  []
  [time_max]
    type = TimeExtremeValue
    postprocessor = max
  []
  [time_min]
    type = TimeExtremeValue
    postprocessor = min
    value_type = min
  []
  [./eigenstrain_xx]
    type = ElementAverageValue
    variable = eigenstrain_xx
    execute_on = 'initial timestep_end'
  [../]
  [./eigenstrain_yy]
    type = ElementAverageValue
    variable = eigenstrain_yy
    execute_on = 'initial timestep_end'
  [../]

  [./total_strain_xx]
    type = ElementAverageValue
    variable = total_strain_xx
    execute_on = 'initial timestep_end'
  [../]
  [./total_strain_yy]
    type = ElementAverageValue
    variable = total_strain_yy
    execute_on = 'initial timestep_end'
  [../]

  [./temperature]
    type = AverageNodalVariableValue
    variable = temp
    execute_on = 'initial timestep_end'
  [../]
  [average_temperature]
    type = ElementAverageValue
    variable = temp
  []
  [inlet_heat_flux]
    type = ADSideFluxAverage
    variable = temp
    boundary = Top
    diffusivity = thermal_conductivity
  []
[]


[Executioner]
  type = Transient
  solve_type = 'Newton'
  end_time = 10
  dt = 0.01
  petsc_options_iname = '-pc_type -ksp_gmres_restart'
  petsc_options_value = 'ilu      101'
  nl_rel_tol = 1e-6
  l_abs_tol = 1e-6
  timestep_tolerance = 1e-6
  automatic_scaling = true
[]


[Outputs]
  exodus = true
[]