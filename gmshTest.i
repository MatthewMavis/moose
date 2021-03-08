
[Mesh]
    [gmshTest]
        type = gmshFile
        Hole_radius = 0.005
        Cooling_Tube_Thickness = 0.002
        Intermediate_Thickness = 0.001
        Small_Hole_Radius = 0.0001
        Angle_Between_Holes = 15
        HoleAmount = 0
        file = DivertorSimple.msh
        geofile = DivertorSimple.geo
        Thermal_Slit_Width = 0.0002
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
    type = RankTwoAux
    rank_two_tensor = eigenstrain
    variable = eigenstrain_yy
    index_i = 1
    index_j = 1
    execute_on = 'initial timestep_end'
  [../]
  [./eigenstrain_xx]
    type = RankTwoAux
    rank_two_tensor = eigenstrain
    variable = eigenstrain_xx
    index_i = 0
    index_j = 0
    execute_on = 'initial timestep_end'
  [../]

  [./total_strain_yy]
    type = RankTwoAux
    rank_two_tensor = total_strain
    variable = total_strain_yy
    index_i = 1
    index_j = 1
    execute_on = 'initial timestep_end'
  [../]
  [./total_strain_xx]
    type = RankTwoAux
    rank_two_tensor = total_strain
    variable = total_strain_xx
    index_i = 0
    index_j = 0
    execute_on = 'initial timestep_end'
  [../]
[]

[Modules]
  [./TensorMechanics]
    [./Master]
      [./all]
        strain = SMALL
        incremental = true
        add_variables = true
        eigenstrain_names = eigenstrain
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
  [H20_thermal]
    type = ADHeatConductionMaterial
    specific_heat = 4187 # J/kg-K
    thermal_conductivity = 0.6 # W/m*K
    block = Hole
  []
  [H20_density]
    type = ADGenericConstantMaterial
    prop_names = 'density'
    prop_values = '997' #kg/m^3 @ 296K
    block = Hole
  []
  [./elasticity_tensor_tungsten]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 390
    poissons_ratio = 0.27
    block = Tungsten
  [../]
  [./thermal_expansion_strain_tungsten]
    type = ComputeThermalExpansionEigenstrain
    stress_free_temperature = 1300
    thermal_expansion_coeff = 4.3e-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = Tungsten
  [../]
  [./elasticity_tensor_CoolingTube]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 121
    poissons_ratio = 0.34
    block = CoolingTube
  [../]
  [./thermal_expansion_strain_CoolingTube]
    type = ComputeThermalExpansionEigenstrain
    stress_free_temperature = 450
    thermal_expansion_coeff = 16.7e-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = CoolingTube
  [../]
  [./elasticity_tensor_Itermediate]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 137
    poissons_ratio = 0.3
    block = Intermediate
  [../]
  [./thermal_expansion_strain_Itermediate]
    type = ComputeThermalExpansionEigenstrain
    stress_free_temperature = 450
    thermal_expansion_coeff = 17e-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = Intermediate
  [../]
  [./elasticity_tensor_Hole]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 2.2
    poissons_ratio = 0.1
    block = Hole
  [../]
  [./thermal_expansion_strain_Hole]
    type = ComputeThermalExpansionEigenstrain
    stress_free_temperature = 278
    thermal_expansion_coeff = 69e-6
    temperature = temp
    eigenstrain_name = eigenstrain
    block = Hole
  [../]
  [./small_stress]
    type = ComputeFiniteStrainElasticStress
  [../]
[]

[BCs]
  [Heat_In]
    type = DirichletBC
    variable = temp
    boundary = Top
    value =  3367 # 100 kW/m^2
  []
  [Heat_Out]
    type = ADConvectiveHeatFluxBC
    variable = temp
    boundary = Tube_Hole_Boundary
    T_infinity = 300 #K
    heat_transfer_coefficient = 10
  []
  [Tung_Int_boundary]
    type = ADConvectiveHeatFluxBC
    variable = temp
    boundary = Tung_Int_Boundary
    T_infinity = 300 #K
    heat_transfer_coefficient = 10
  []
  [x_top]
    type = DirichletBC
    variable = disp_x
    boundary = Top
    value = 0.0
  []
  [y_top]
    type = DirichletBC
    variable = disp_y
    boundary = Top
    value = 0.0
  []
[]

[Preconditioning]
  [SMP]
    type = SMP
    full = true
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
[]


[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  end_time = 10
  dt = 0.1
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_tol = 1e-6
  l_abs_tol = 1e-6
  timestep_tolerance = 1e-6
[]


[Outputs]
  exodus = true
[]