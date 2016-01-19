/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * dm_activator_base.c
 *
 *  \date       26 Jul 2014
 *  \author     <a href="mailto:dev@celix.apache.org">Apache Celix Project Team</a>
 *  \copyright  Apache License, Version 2.0
 */


#include <stdlib.h>

#include "bundle_activator.h"
#include "dm_activator_base.h"


struct dm_dependency_activator_base {
	dm_dependency_manager_pt manager;
	bundle_context_pt context;
	void* userData;
};

typedef struct dm_dependency_activator_base * dependency_activator_base_pt;

celix_status_t bundleActivator_create(bundle_context_pt context, void **userData) {
	celix_status_t status = CELIX_ENOMEM;

	dependency_activator_base_pt dependency_activator = calloc(1, sizeof(struct dm_dependency_activator_base));

	if (dependency_activator) {
		dependency_activator->context = context;
		dm_create(context, &dependency_activator->userData);

		(*userData) = dependency_activator;

		status = CELIX_SUCCESS;
	}

	return status;
}

celix_status_t bundleActivator_start(void * userData, bundle_context_pt context) {
	celix_status_t status;
	dependency_activator_base_pt dependency_activator = (dependency_activator_base_pt) userData;

	status = dependencyManager_create(dependency_activator->context, &dependency_activator->manager);

	if (status == CELIX_SUCCESS) {
		dm_init(dependency_activator->userData, context, dependency_activator->manager);
	}

	return status;
}

celix_status_t bundleActivator_stop(void * userData, bundle_context_pt context __attribute__((unused))) {
	celix_status_t status = CELIX_SUCCESS;
	dependency_activator_base_pt dependency_activator = (dependency_activator_base_pt) userData;

	dm_destroy(dependency_activator->userData, dependency_activator->context, dependency_activator->manager);

	dependencyManager_destroy(&dependency_activator->manager);

	dependency_activator->userData = NULL;
	dependency_activator->manager = NULL;

	return status;
}

celix_status_t bundleActivator_destroy(void * userData, bundle_context_pt context __attribute__((unused))) {
	celix_status_t status = CELIX_SUCCESS;
	dependency_activator_base_pt dependency_activator = (dependency_activator_base_pt) userData;

	free(dependency_activator);

	return status;
}

